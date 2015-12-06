function simulate_brachia_bot()

	addpath([pwd '/Obstacles'])
	addpath([pwd '/Optimization'])
	addpath([pwd '/Derived'])

    desired_rung = 2;

    %fixed params
    m1 = 0.55;
    m2 = m1;
    l1 = 0.30;%length of links
    l2 = l1;
    I1 = 1/3*m1*l1^2;%model as rod rotating around one end
    I2 = 1/3*m2*l2^2;
    c1 = 0.5*l1;%location of center of mass along link
    c2 = 0.5*l2;
    g = 9.81;
    
    %lattice params
    lattice_pitch  = 0.35;%meters
    
    % initial conditions
    th1_0 = 0.3;
    th2_0 = 2*pi/3;
    dth1_0 = 0;
    dth2_0 = 0;
    
    p = [l1; l2; c1; c2; m1; m2; I1; I2; g; lattice_pitch];% parameters array
    
    %first solve system with just swinging and obstacle avoidance
    tspan = [0 20];
    inttol = 1e-2;
    z0 = [th1_0; th2_0; dth1_0; dth2_0];
    opts = odeset('AbsTol', inttol, 'RelTol', inttol);
    sol = ode45(@swinging_dynamics,tspan,z0,opts,p);
    
    %then find pt of sufficient energy and solve for trajectory to reach
    %target rung

    %compute energy
    E = energy_brachia_bot(sol.y, p);
    z_des = final_z(desired_rung, l1, lattice_pitch);
    
%     z0_opt = get_opt_z0(E, z_des, sol.y, p);
%     
%     tf = .5;                                        % simulation final time
%     ctrl.tf = 0.4;                                  % control time points
%     ctrl.T = [1.5 1.5 1.5];  
%     
%     problem.objective = @(x) objective(x,z0_opt,p);     % create anonymous function that returns objective
%     problem.nonlcon = @(x) constraints(x,z0_opt,p);     % create anonymous function that returns nonlinear constraints
%     problem.x0 = [tf ctrl.tf ctrl.T];                   % initial guess for decision variables
%     problem.lb = [.1 .1 -2*ones(size(ctrl.T))];     % lower bound on decision variables
%     problem.ub = [1  1   2*ones(size(ctrl.T))];     % upper bound on decision variables
%     problem.Aineq = []; problem.bineq = [];         % no linear inequality constraints
%     problem.Aeq = []; problem.beq = [];             % no linear equality constraints
%     problem.options = optimset('Display','iter');   % set options
%     problem.solver = 'fmincon';                     % required
%     x = fmincon(problem);                           % solve nonlinear programming problem
% 
%     % Note that once you've solved the optimization problem, you'll need to 
%     % re-define tf, tfc, and ctrl here to reflect your solution.
%     tf = x(1);
%     ctrl.tf = x(2);
%     ctrl.T = [x(3) x(4) x(5)];
% 
%     [t_opt, z_opt, u_opt, indices_opt] = hybrid_simulation(z0_opt,ctrl,p,[0 tf]); % run simulation
    
    
    %combine energy incr and optimization results and plot
    
    
    
    figure(1); clf;
    plot(sol.x,E);xlabel('Time (s)'); ylabel('Energy (J)');
    sprintf('%4.11f',max(E) - min(E));%print out max change in energy
    
    %plot thetas
    theta1 = sol.y(1, :);
    theta2 = sol.y(2, :);
    figure(2); clf;
    plot(sol.x,theta1);xlabel('Time (s)'); ylabel('Theta 1 (rad)');
    figure(3); clf;
    plot(sol.x,theta2);xlabel('Time (s)'); ylabel('Theta 2 (rad)');
    
%     %plot dthetas
%     dtheta1 = sol.y(3, :);
%     dtheta2 = sol.y(4, :);
%     figure(4); clf;
%     plot(sol.x,dtheta1);xlabel('Time (s)'); ylabel('dTheta 1 (rad/s)');
%     figure(5); clf;
%     plot(sol.x,dtheta2);xlabel('Time (s)'); ylabel('dTheta 2 (rad/s)');
    
    sizeSol = size(sol.y);
    taus = zeros(sizeSol(2), 1);
    for i=1:sizeSol(2)
        z = sol.y(:,i);
        taus(i) = calc_tau(z, p);
    end
    figure(6); clf;
	plot(sol.x,taus);xlabel('Time (s)'); ylabel('Torque');

    %animate
    figure(7); clf;
    [potential_map, X_contour, Y_contour] = obstacle_potential_map(lattice_pitch);
    contour(X_contour, Y_contour, potential_map);
    animateSol(sol,p);
    
end

function animateSol(sol, p)
    % Prepare plot handles
    hold on
    line_width = 0.5;
    h_link1 = plot([0],[0], 'LineWidth', line_width);
    h_link2 = plot([0],[0], 'LineWidth', line_width);
    xlabel('x')
    ylabel('y');
    h_title = title('t=0.0s');
    
    %plot lattice
    pitch = p(10);
    for i = -1:1
        for j= -1:1
            plot(i*pitch, j*pitch, 'o', 'MarkerEdgeColor', 'k');
        end
    end
    
    
    
    axis equal
    axis([-2*pitch 2*pitch -2*pitch 2*pitch]);
    
    %Step through and update animation
    for t = 0:.01:sol.x(end)
        % interpolate to get state at current time.
        z = interp1(sol.x',sol.y',t)';
        keypoints = keypoints_brachia_bot(z,p);

        r_B = keypoints(1:2); % Vector to joint B
        r_C = keypoints(3:4); % Vector to joint C

        set(h_title,'String',  sprintf('t=%.2f',t) ); % update title
        
        % Plot Link 1
        set(h_link1,'XData' , [0 r_B(1)] );
        set(h_link1,'YData' , [0 r_B(2)] );

        % Plot Link 2
        set(h_link2,'XData' , [r_B(1) r_C(1)] );
        set(h_link2,'YData' , [r_B(2) r_C(2)] );

        pause(.01)
    end
end