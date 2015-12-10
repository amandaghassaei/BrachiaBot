function theta_des = calc_theta_targeting_2(z, p)

    theta_des = 0;

    th1 = z(1);
    th2 = z(2);
    dth1 = z(3);
    dth2 = z(4);
       
    target_approach_direction = sign(dth1);
    th2_final = final_angle_th2(z, p(11), p(10), p(1));
    th1_final = final_angle_th1(z, p(11), p(10), p(1));
    
    target_approach_direction_des = target_theta_sign(p(11));

    theta_des = th2_final;

end

