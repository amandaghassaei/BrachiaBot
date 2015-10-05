function simulate_brachia_bot()

    %fixed params
    m1 = 0.2;
    m2 = 1;
    m3 = m2;
    m4 = m1;
    I1 = 0.05;
    I2 = 0.05;
    I3 = I2;
    I4 = I1;
    l1 = 0.2;
    l2 = 1;
    l3 = l2;
    l4 = l1;
    c1 = 0.5*l1;
    c2 = 0.5*l2;
    c3 = 0.5*l3;
    c4 = 0.5*l4;
    g = 9.81;
    
    th1_0 = 1.5;
    th2_0 = 0;
    th3_0 = 0;
    th4_0 = 0;
    dth1_0 = 0;
    dth2_0 = 0;
    dth3_0 = 0;
    dth4_0 = 0;
    
    p = [l1; l2; l3; l4; c1; c2; c3; c4; m1; m2; m3; m4; I1; I2; I3; I4; g];% parameters array
    
    tspan = [0 10];
    inttol = 1e-6;
    z0 = [th1_0; th2_0; th3_0; th4_0; dth1_0; dth2_0; dth3_0; dth4_0];
    opts = odeset('AbsTol', inttol, 'RelTol', inttol);
    sol = ode45(@dynamics,tspan,z0,opts,p);

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
    
%     %contour plot
%     PotentialMat = zeros(201,201);
%     thetas = zeros(1, 201);
%     for i=-100:100
%         theta1 = i/101*2*pi;
%         for j=-100:100
%             theta2 = j/101.0*2*pi;
%             PotentialMat(i+101,j+101) = potential_brachia_bot(theta1, theta2, p);
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

function animateSol(sol,p)
    % Prepare plot handles
    hold on
    h_link1 = plot([0],[0],'LineWidth',5);
    h_link2 = plot([0],[0],'LineWidth',5);
    h_link3 = plot([0],[0],'LineWidth',5);
    h_link4 = plot([0],[0],'LineWidth',5);
    xlabel('x')
    ylabel('y');
    h_title = title('t=0.0s');
    
    axis equal
    axis([-2 2 -2 1]);
    
    %Step through and update animation
    for t = 0:.01:sol.x(end)
        % interpolate to get state at current time.
        z = interp1(sol.x',sol.y',t)';
        keypoints = keypoints_brachia_bot(z,p);

        r_B = keypoints(1:2); % Vector to joint B
        r_C = keypoints(3:4); % Vector to joint C
        r_D = keypoints(5:6); % Vector to joint D
        r_E = keypoints(7:8); % Vector to joint E

        set(h_title,'String',  sprintf('t=%.2f',t) ); % update title
        
        % Plot Link 1
        set(h_link1,'XData' , [0 r_B(1)] );
        set(h_link1,'YData' , [0 r_B(2)] );

        % Plot Link 2
        set(h_link2,'XData' , [r_B(1) r_C(1)] );
        set(h_link2,'YData' , [r_B(2) r_C(2)] );
        
        % Plot Link 3
        set(h_link3,'XData' , [r_C(1) r_D(1)] );
        set(h_link3,'YData' , [r_C(2) r_D(2)] );
        
        % Plot Link 3
        set(h_link4,'XData' , [r_D(1) r_E(1)] );
        set(h_link4,'YData' , [r_D(2) r_E(2)] );

        pause(.01)
    end
end