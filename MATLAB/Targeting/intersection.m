function intersection = intersection(z, p)

    motor_position = motor_pos(z, p);
    gripper_position = gripper_pos(z, p);
    link2_slope = gripper_pos-motor_pos;
    
    ylink2 = link2_slope(xlink2-motor_position(1)) + motor_position(2);

    rung_pos = rung_position(p(11). p(10));
    

end

