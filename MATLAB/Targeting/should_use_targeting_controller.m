function use_targeting = should_use_targeting_controller(z, p)
    use_targeting = false;

    th1 = z(1);
    th2 = z(2);
    dth1 = z(3);
    dth2 = z(4);
    
    
    E = energy_brachia_bot(z, p);
    
    th2_final = final_angle_th2(z, p(11), p(10), p(1));
    th1_final = final_angle_th1(z, p(11), p(10), p(1));
    dth1_final = 2;
    
    E_des = energy_brachia_bot([th1_final; th2_final; dth1_final; 0], p);
    
    if E<E_des
        return
    end
    if abs(dth1) < dth1_final
        return;
    end
        
    target_approach_direction = 1;
    if dth1<0
        target_approach_direction = -1;
    end
    target_approach_direction_des = target_theta_sign(p(11));
    
    if target_approach_direction_des ~= 0 && target_approach_direction ~= target_approach_direction_des
        return;
    end
       
    if target_approach_direction*th1 > target_approach_direction*th1_final - pi/4
        use_targeting = true;
    end
end

