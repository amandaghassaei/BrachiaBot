function simulate_brachia_bot()

	addpath([pwd '/Obstacles'])
	addpath([pwd '/Optimization'])
	addpath([pwd '/Derived'])
    addpath([pwd '/Targeting'])

    desired_rung = 1;
    
    m1 = 0.93159230;
    m2 = 0.45433433;
    l1 = 0.275;%length of links
    l2 = l1;
    I1 = 0.03736067;
    I2 = 0.01778165;
    c1 = l1-0.08567346;%location of center of mass along link
    c2 = 0.17594269;
    g = 9.81;
    lattice_pitch  = 0.35;%meters
    
    % initial conditions
    th1_0 = -0.3;
    th2_0 = -2/3*pi;
    dth1_0 = 0;
    dth2_0 = 0;
    
    p = [l1; l2; c1; c2; m1; m2; I1; I2; g; lattice_pitch; desired_rung];% parameters array
   
    global is_targeting;
    is_targeting = 0;
    
    
    %first solve system with just swinging and obstacle avoidance
    tspan = [0 20];
    inttol = 1e-2;
    z0 = [th1_0; th2_0; dth1_0; dth2_0];
    opts = odeset('AbsTol', inttol, 'RelTol', inttol);
    sol = ode45(@swinging_dynamics,tspan,z0,opts,p);
    
    %compute energy
    E = energy_brachia_bot(sol.y, p);
    
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
    
%     sizeSol = size(sol.y);
%     taus = zeros(sizeSol(2), 1);
%     for i=1:sizeSol(2)
%         z = sol.y(:,i);
%         taus(i) = calc_tau(z, p, sol.x(i));
%     end
%     figure(6); clf;
% 	plot(sol.x,taus);xlabel('Time (s)'); ylabel('Torque');

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