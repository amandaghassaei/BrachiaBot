function force = obstacle_avoidance(z, p)

    % Get angles
    th1 = z(1);
    th2 = z(2);
    
    % Get velocities
    dth1 = z(3);
    dth2 = z(4);
    
    K = 10;
    D = 1;
        
    potential = obstacle_potential(z, p)/100;
    force = sign(th2)*(K*potential-D*dth2);

end

