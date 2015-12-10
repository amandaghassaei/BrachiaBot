function theta_des = calc_theta_targeting(z, p)

    theta_des = 0;

    th1 = z(1);
    th2 = z(2);
    dth1 = z(3);
    dth2 = z(4);
    
    
    E = energy_brachia_bot(z, p);
    
    target_approach_direction = sign(dth1);
    th2_final = final_angle_th2(z, p(11), p(10), p(1));
    th1_final = final_angle_th1(z, p(11), p(10), p(1));
    
    E_des = energy_brachia_bot([th1_final; th2_final; 0; 0], p);
    
    target_approach_direction_des = target_theta_sign(p(11));
    
    if E<E_des
        return
    end
%     theta_des = th2_final;

    
%     if E>E_des && target_approach_direction ~= 0 && target_approach_direction ~= sign(dth1)
%         return
%     end
            
    if (target_approach_direction)
        %moving toward the right
        if E<E_des && th1<th1_final/2
            return
        end
        
        theta_des = th2_final;
    else
        %moving toward the left
        if E<E_des && th1>th1_final/2
            return
        end
        
        theta_des = th2_final;
    end
        

    
    
    

end

