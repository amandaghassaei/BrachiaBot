function simulate_brachia_bot()

    desired_rung = 2;

    %fixed params
    m1 = 1;
    m2 = m1;
    l1 = 0.250;%length of links
    l2 = l1;
    I1 = 1/3*m1*l1^2;%model as rod rotating around one end
    I2 = 1/3*m2*l2^2;
    c1 = 0.5*l1;%location of center of mass along link
    c2 = 0.5*l2;
    g = 9.81;
    
    %lattice params
    lattice_pitch  = 0.45;% 200 mm
    lattice_options = struct('lattice_pitch', lattice_pitch);
    
    % initial conditions
    th1_0 = 0.3;
    th2_0 = 0;
    dth1_0 = 0;
    dth2_0 = 0;
    
    p = [l1; l2; c1; c2; m1; m2; I1; I2; g];% parameters array
    
    E_des = calc_energy_needed(desired_rung, l1, lattice_pitch, p);
    
    tspan = [0 10];
    inttol = 1e-2;
    z0 = [th1_0; th2_0; dth1_0; dth2_0];
    opts = odeset('AbsTol', inttol, 'RelTol', inttol);
    sol = ode45(@swinging_dynamics,tspan,z0,opts,p,E_des,lattice_options);

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
    
    %animate
    figure(5); clf;
    animateSol(sol,p,lattice_options);

end

function animateSol(sol, p, options)
    % Prepare plot handles
    hold on
    line_width = 0.5;
    h_link1 = plot([0],[0], 'LineWidth', line_width);
    h_link2 = plot([0],[0], 'LineWidth', line_width);
    xlabel('x')
    ylabel('y');
    h_title = title('t=0.0s');
    
    %plot lattice
    pitch = options.lattice_pitch;
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