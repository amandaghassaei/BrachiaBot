function potential = obstacle_potential_xy(x, y, pitch)
    
    potential = 0;
    for i=-1:1
        for j=-1:1
            if i==0 && j==0
                continue;
            end
            rung_pos = [i*pitch; j*pitch];
            distance = norm([x;y] - rung_pos);
            potential = potential + (1/distance)^1;
        end
    end

end

