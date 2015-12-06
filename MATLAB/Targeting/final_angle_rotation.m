function rotation = final_angle_rotation(z, target_rung)
%    1   2   3
%    4   5   6
%    7   8   9
    
    rotation = 0;

    if target_rung == 2
        if z(3) < 0%approach from right
            rotation = -pi/2;
        else
            rotation = pi/2;
        end
    elseif target_rung == 8
        if z(3) < 0%approach from right
            rotation = pi/2;
        else
            rotation = -pi/2;
        end
    elseif target_rung == 1
        rotation = -pi/4;
    elseif target_rung == 3
        rotation = pi/4;
    elseif target_rung == 7
        rotation = pi/4;
    elseif target_rung == 9
        rotation = -pi/4;
    end
end

