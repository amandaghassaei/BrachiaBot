function angle = final_angle(z, target_rung, lattice_pitch, link_length)
    
    if (target_is_cardinal(target_rung))
        angle = 2*asin(1/2*lattice_pitch/link_length);
    else
        angle = 2*asin(1/2*lattice_pitch*sqrt(2)/link_length);
    end
    
    if (z(3)<0) angle = angle * -1;
end

