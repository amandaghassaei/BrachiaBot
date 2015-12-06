function intersection = intersection(z, p)

    motor_position = motor_pos(z, p);
    gripper_position = gripper_pos(z, p);
    link2_slope = gripper_position-motor_pos;
    
%     y = link2_slope(x-motor_position(1)) + motor_position(2);

    rung_pos = rung_position(p(11). p(10));
    traj_slope = tan(pi/2-final_angle(p(11), p(10), p(1))/2 + final_angle_rotation(z, p(11)));
    
%     y = traj_slope*(x-rung_pox(1)) + rung_pos(2);
    
    x = (-traj_slope*rung_pox(1) + rung_pos(2) -link2_slope*motor_position(1) + motor_position(2))/(link2_slope-traj_slope);
    y = traj_slope*(x-rung_pox(1)) + rung_pos(2);

    intersection = [x;y;0];
    
end

