function is_cardinal = target_is_cardinal(target_rung)
%    1   2   3
%    4   5   6
%    7   8   9

    if mod(target_rung, 2) == 0
        is_cardinal = true;
    else
        is_cardinal = false;
    end
end

