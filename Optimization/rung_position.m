function position = rung_position(target_rung, pitch)

% 1  2  3
% 4     5
% 6  7  8
    
    if target_rung == 2
        x_pos = 0;
        y_pos = pitch;
    elseif target_rung == 4
        x_pos = -pitch;
        y_pos = 0;
    elseif target_rung == 5
        x_pos = pitch;
        y_pos = 0;
    elseif target_rung == 7
        x_pos = 0;
        y_pos = -pitch;
    else
        warning('invalid target_rung');
        return;
    end

    position = [x_pos, y_pos];

end

