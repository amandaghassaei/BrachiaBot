function [potential_map, X, Y] = force_potential_map(p, pitch)

    resolution = 0.01;
    contour_size = round(pitch/resolution*3);
    potential_map = zeros(contour_size, contour_size);
    X = -pitch*1.5:resolution:pitch*1.5;
    Y = -pitch*1.5:resolution:pitch*1.5;
    
    x_index = 0;
    for x=-pitch*1.5:resolution:pitch*1.5
        x_index = x_index + 1;
        y_index = 0;
        for y=-pitch*1.5:resolution:pitch*1.5
            y_index = y_index + 1;
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
            potential_map(x_index,y_index) = potential;
        end
    end
end