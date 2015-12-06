function theta = theta_for_intersection(z, p, intersection)
    
    motor_position = motor_pos(z, p);
    angle = atan2(motor_position(1)-intersection(1), motor_position(2)-intersection(2));
    theta = angle-z(1);

end

