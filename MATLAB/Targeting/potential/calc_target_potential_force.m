function force = calc_target_potential_force(z, p)

    % Get angles
    th1 = z(1);
    th2 = z(2);
    
    % Get velocities
    dth1 = z(3);
    dth2 = z(4);
    
    K = 10;
    D = 1;
        
    potential = target_potential(z, p)/100;
    force = -potential_direction(th1, th2, dth1, dth2)*(K*potential-D*dth2);

end

