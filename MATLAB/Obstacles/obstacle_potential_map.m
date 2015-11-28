function [potential_map, X, Y] = obstacle_potential_map(pitch)

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
            potential_map(x_index,y_index) = obstacle_potential_xy(x,y,pitch);
        end
    end
end