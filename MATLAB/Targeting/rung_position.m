function position = rung_position(target_rung, lattice_pitch)
%    1   2   3
%    4   5   6
%    7   8   9
    
    x = mod(target_rung-1, 3)-1;
    y = 1-floor((target_rung-1)/3);
    position = [lattice_pitch*x; lattice_pitch*y];

end

