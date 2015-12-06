function angle = final_angle(target_rung, lattice_pitch, link_length)
    
    if (target_is_cardinal(target_rung))
        angle = 2*asin(1/2*lattice_pitch/link_length);
    else
        angle = 2*asin(1/2*lattice_pitch*sqrt(2)/link_length);
    end
end

