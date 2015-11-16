function energy_needed = calc_energy_needed(target_rung, arm_length, pitch, p)
% 1  2  3
% 4     5
% 6  7  8
    
    if target_rung == 2
        x_pos = 0;
        y_pos = pitch;
        th1_offset = pi;
    elseif target_rung == 4
        x_pos = -pitch;
        y_pos = 0;
        th1_offset = pi/2;
    elseif target_rung == 5
        x_pos = pitch;
        y_pos = 0;
        th1_offset = pi/2;
    elseif target_rung == 7
        x_pos = 0;
        y_pos = -pitch;
        th1_offset = 0;
    else
        energy_needed = 0;
        warning('invalid target_rung');
        return;
    end
        
    dist_to_target_rung = norm([x_pos, y_pos]);
        
    th1 = acos(1/2*dist_to_target_rung/arm_length);
    th2 = pi - 2*(pi/2-th1);
    th1 = th1_offset - th1;
    
    z = [th1;th2;0;0];
    energy_needed = energy_brachia_bot(z, p);
end

