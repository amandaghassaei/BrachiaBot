function simulate_double_pendulum()

    %fixed params
    m1 = 1;
    m2 = 1;
    I1 = 0.05;
    I2 = 0.05;
    l1 = 1;
    l2 = 0.5;
    c1 = 0.5;
    c2 = 0.25;
    g = 9.81;
    
    th1_0 = 3;
    th2_0 = 0;
    dth1_0 = 0;
    dth2_0 = 0;
    
    p   = [l1; l2; c1; c2; m1; m2; I1; I2; g];% parameters array
    
    tspan = [0 10];
    inttol = 1e-6;
    z0 = [th1_0; th2_0; dth1_0; dth2_0];
    opts = odeset('AbsTol', inttol, 'RelTol', inttol);
    sol = ode45(@dynamics,tspan,z0,opts,p);

    %compute energy
    E = energy_double_pendulum(sol.y, p);
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
    
%     %contour plot
%     PotentialMat = zeros(201,201);
%     thetas = zeros(1, 201);
%     for i=-100:100
%         theta1 = i/101*2*pi;
%         for j=-100:100
%             theta2 = j/101.0*2*pi;
%             PotentialMat(i+101,j+101) = potential_double_pendulum(theta1, theta2, p);
%         end
%         thetas(i+101) = i/101*2*pi;
%     end
%     figure(4); clf;
%     hold on
%     plot(sol.y(1,:),sol.y(2,:),'k','LineWidth',3);
%     xlabel('Theta 1 (rad)'); ylabel('Theta 2 (rad)');
%     contour(thetas, thetas, PotentialMat, 70);
    
    %animate
    figure(5); clf;
    animateSol(sol,p);

end

function dz = dynamics(t, z, p)
    
    % Get mass matrix
    A = A_double_pendulum(z,p);
    
    % Get forces
    dtheta1 = z(3);
    dtheta2 = z(4);
    t1 = 0;%-dtheta1;
    t2 = 0;%-dtheta2;
    u = [t1 t2]';
    b = b_double_pendulum(z,u, p);
    
    % Solve for qdd
    qdd = A\b;
    dz = 0*z;
    
    % Form dz
    dz(1:2) = z(3:4);
    dz(3:4) = qdd;

end

function animateSol(sol,p)
    % Prepare plot handles
    hold on
    h_link1 = plot([0],[0],'LineWidth',5);
    h_link2 = plot([0],[0],'LineWidth',5);
    xlabel('x')
    ylabel('y');
    h_title = title('t=0.0s');
    
    axis equal
    axis([-2 2 -2 1]);
    
    %Step through and update animation
    for t = 0:.01:sol.x(end)
        % interpolate to get state at current time.
        z = interp1(sol.x',sol.y',t)';
        keypoints = keypoints_double_pendulum(z,p);

        rB = keypoints(1:2); % Vector to joint B
        rC = keypoints(3:4); % Vector to joint C

        set(h_title,'String',  sprintf('t=%.2f',t) ); % update title
        
        % Plot Link 1
        set(h_link1,'XData' , [0 rB(1)] );
        set(h_link1,'YData' , [0 rB(2)] );

        % Plot Link 2
        set(h_link2,'XData' , [rB(1) rC(1)] );
        set(h_link2,'YData' , [rB(2) rC(2)] );

        pause(.01)
    end
end