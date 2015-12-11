function override = should_override_targeting_controller(z, p)
    
    override = true;
    
    th1 = z(1);
    th2 = z(2);
    dth1 = z(3);
    dth2 = z(4);
    
    th1_final = final_angle_th1(z, p(11), p(10), p(1));
    
    num_turns = fix(th1/(2*pi));
    th1_rel = th1-num_turns*2*pi;
    
    target_approach_direction = 1;
    if th2<0
        target_approach_direction = -1;
    end
    
    th1_direction = 1;
    if dth1<0
        th1_direction = -1;
    end

    if target_approach_direction*th1_rel > target_approach_direction*th1_final - pi/8
        override = false;
        return;
    end
        
    if th1_direction ~= target_approach_direction
        return;
    end
    
    override = false;

end

