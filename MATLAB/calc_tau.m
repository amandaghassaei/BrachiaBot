function tau = calc_tau(z, p, t)
    
    % Get angles
    th1 = z(1);
    th2 = z(2);
    
    % Get velocities
    dth1 = z(3);
    dth2 = z(4);
        
    % Forces
    E = energy_brachia_bot(z, p);
    
    % Get mass matrix
    A = A_brachia_bot(z,p);
    A_hat = A(2,2)-A(2,1)*A(1,2)/A(1,1);
    
    corr_centrip_comp = corr_brachia_bot(z, p);
    corr_centrip_comp_hat = corr_centrip_comp(2)-A(2,1)*corr_centrip_comp(1)/A(1,1);
    
    grav_comp = grav_brachia_bot(z, p);
    grav_com_hat = grav_comp(2)-A(2,1)*grav_comp(1)/A(1,1);
    
    
    K = 100;
    D = 10;
    
%     z_des = final_z(2, p(1), p(10));
    global is_targeting;
    force = 0;
    if is_targeting && should_override_targeting_controller(z, p)
        is_targeting = false;
%         t
    elseif t>1 && (is_targeting || should_use_targeting_controller(z, p))
        distance = abs(final_angle_th1(z, p(11), p(10), p(1)) - th1);
%         Kamp = 10-9*distance;
%         if Kamp < 1
%             Kamp = 1;
%         end
%         K = Kamp*K;
%         D = Kamp*10;
%         if (is_targeting == 0)
%             a = t
%             dth1
%         end
        force = calc_theta_targeting_2(z, p, is_targeting == 0);
        is_targeting = 1;
        
    else
        th2_des = theta_desired(-2.35, 2.35, th1, th2, dth1, dth2);%143 degrees soft stop
%         th2_des = obstacle_th2(z, p, th2_des);
        [K, D] = calculate_swing_up_gains(z, p, th2_des);
        force = K*(th2_des - th2) - D*dth2;
    end
    
    
        
    A_hat = 0.02;
    
    tau = A_hat*force + corr_centrip_comp_hat + grav_com_hat;

%     obstacleAvoidance = 0;%obstacle_avoidance(z, p);

    % Compute virtual foce
%     J = gripper_jacobian;
%     lambda = A*J_inv;

    
%     tau = obstacleAvoidance + energyIncr;

end

function [K, D] = calculate_swing_up_gains(z, p, th_des)
    
    K = 100;
    D = 10;

    th1 = z(1);
    th2 = z(2);
    
    % Get velocities
    dth1 = z(3);
    dth2 = z(4);
    
    if (dth1<0 && th2<th_des) || (dth1>0 && th2>th_des)
        K = 1000;
        D = 100;
    end
end

function theta = theta_desired(range_min, range_max, th1, th2, dth1, dth2)

    num_turns = fix(th1/(2*pi));
    th1_rel = th1-num_turns*2*pi;
%     if abs(th1_rel) > pi
%         th1_rel  = sign(th1_rel)*(abs(th1_rel)-pi);
%     end

    if dth1<0
        theta = range_min*abs(cos(th1_rel/2));
    else
        theta = range_max*abs(cos(th1_rel/2));
    end
    
%     theta = sign_nonzero(dth1)*(range*abs(cos(th1_rel/2)));%-abs(th1_rel));%*cos(th1)
        
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
