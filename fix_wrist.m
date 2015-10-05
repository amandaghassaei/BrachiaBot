function z = fix_wrist(z)

    %lock the wrists
    z(6) = 0;% dth2 = 0
    z(8) = 0;% dth4 = 0

end