function z = final_z(target_rung, arm_length, pitch)

    target_position = rung_position(target_rung, pitch);

    if target_rung == 2
        th1_offset = pi;%[pi, -pi];
    elseif target_rung == 4
        th1_offset = -pi/2;
    elseif target_rung == 5
        th1_offset = pi/2;
    elseif target_rung == 7
        th1_offset = 0;%[0, 0];
    end
        
    dist_to_target_rung = norm(target_position);
        
    th1 = acos(1/2*dist_to_target_rung/arm_length);
    th2 = pi - 2*(pi/2-th1);
    
    th1 = th1_offset - th1;
    
    z = [th1;th2;0;0];
end

