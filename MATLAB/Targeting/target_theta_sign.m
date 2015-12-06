function sign = target_theta_sign(target_rung)
%    1   2   3
%    4   5   6
%    7   8   9

    if target_rung == 1 || target_rung == 4  || target_rung == 7
        sign = -1;
    elseif target_rung == 3 || target_rung == 6  || target_rung == 9
        sign = 1;
    else
        sign = 0;
    end


end

