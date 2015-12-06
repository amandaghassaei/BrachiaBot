function theta_des = calc_theta_desired(z, p)

    theta_des = 0;

    th1 = z(1);
    th2 = z(2);
    dth1 = z(3);
    dth2 = z(4);

    target_approach_direction = target_theta_sign(p(11));
    if target_approach_direction ~= 0 && target_approach_direction ~= sign(dth1)
        return
    end
        
    target_approach_direction = sign(dth1);
    angle = final_angle(z, p(11), p(10), p(1));
    
    if (target_approach_direction)
        %moving toward the right
        if th2<angle/2
            return
        end
        
        
    else
        %moving toward the left
        if th2>angle/2
            return
        end
        
        
    end
        

    
    
    

end

