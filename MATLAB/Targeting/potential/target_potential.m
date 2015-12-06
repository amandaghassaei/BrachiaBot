function potential = target_potential(z, p)
    
    rung_pos = rung_position(p(11), p(10));
    gripper_position = gripper_pos(z, p);
    distance = norm(gripper_position - rung_pos);
    potential = -(1/distance)^2;

end

