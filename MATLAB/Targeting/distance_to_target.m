function distance = distance_to_target(z, p)

    target_position = rung_position(p(11), p(10));
    current_position = gripper_pos(z, p);
    distance = target_position-current_position;

end

