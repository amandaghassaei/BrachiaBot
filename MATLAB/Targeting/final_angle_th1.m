function angle = final_angle_th1(z, target_rung, lattice_pitch, link_length)
    
    if (target_is_cardinal(target_rung))
        angle = asin(1/2*lattice_pitch/link_length);
    else
        angle = asin(1/2*lattice_pitch*sqrt(2)/link_length);
    end
    
    angle  = angle + final_angle_rotation(z, target_rung);
    
    target_approach_direction_des = target_theta_sign(target_rung);
    
    if target_approach_direction_des<0 || (target_approach_direction_des == 0 && z(3)<0)
        angle = angle * -1;
    end
         
end

