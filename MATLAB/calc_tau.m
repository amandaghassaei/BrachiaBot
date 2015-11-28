function tau = calc_tau(z, p)
        
    % Get mass matrix
    A = A_brachia_bot(z,p);
    
    % Get angles
    th1 = z(1);
    th2 = z(2);
    
    % Get velocities
    dth1 = z(3);
    dth2 = z(4);
        
    % Forces
    E = energy_brachia_bot(z, p);
    
    A_hat22 = A(2,2)-A(2,1)*A(1,2)/A(1,1);
    K = 100;
    D = 10;
    
    z_des = final_z(2, p(1), p(10));
    if (energy_brachia_bot(z_des, p) < E)
        th2_des = sign(th2)*2*pi/3;
        K = 1000;
    else
        th2_des = theta_desired(3*pi/6, th1, th2, dth1, dth2);
    end
    
    v = K*(th2_des - th2) - D*dth2;% + k3*u_hat;
    energyIncr = A_hat22*v;

    obstacleAvoidance = 0;%obstacle_avoidance(z, p);

    % Compute virtual foce
%     J = gripper_jacobian;
%     lambda = A*J_inv;

    grav_comp = grav_brachia_bot(z, p);

    %todo coriolis/cetripedal compensation
    corr_centrip_comp = corr_brachia_bot(z, p);% - A_hat22*gripper_jacobian(z,p)*dth2;

    tau = obstacleAvoidance + energyIncr + grav_comp(2) + corr_centrip_comp(2);

end

function theta = theta_desired(range, th1, th2, dth1, dth2)

    num_turns = fix(th1/(2*pi));
    th1_rel = th1-num_turns*2*pi;
%     if abs(th1_rel) > pi
%         th1_rel  = sign(th1_rel)*(abs(th1_rel)-pi);
%     end
    
    theta = sign_nonzero(dth1)*(range-abs(th1_rel));%*cos(th1)
        
%     num_turns = fix(th2/(2*pi));
%     theta = theta + num_turns*2*pi;%shouldn't need this because theta2
%     should never pass PI

end

function mysign = sign_nonzero(val)

    mysign = sign(val);
    if mysign == 0
        mysign = 1;
    end

end