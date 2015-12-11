function position = rung_position(target_rung, pitch)

% 1  2  3
% 4  5  6
% 7  8  9
    
    if target_rung == 1 || target_rung == 4 || target_rung == 7
        x_pos = -pitch;
    elseif target_rung == 2 || target_rung == 5 || target_rung == 8
        x_pos = 0;
    elseif target_rung == 3 || target_rung == 6 || target_rung == 9
        x_pos = pitch;
    else
        return;
    end
    if target_rung < 4
        y_pos = pitch;
    elseif target_rung < 7
        y_pos = 0;
    elseif target_rung < 10
        y_pos = -pitch;
    else
        return
    end

    position = [x_pos, y_pos];

end

