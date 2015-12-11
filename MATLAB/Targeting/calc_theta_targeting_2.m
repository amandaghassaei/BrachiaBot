function force = calc_theta_targeting_2(z, p, should_print)

    th1 = z(1);
    th2 = z(2);
    dth1 = z(3);
    dth2 = z(4);
       
    th2_final = final_angle_th2(z, p(11), p(10), p(1));
    th1_final = final_angle_th1(z, p(11), p(10), p(1));
        
    rung_pos = rung_position(p(11), p(10));
    
    m = 1/tan(th1_final);
    if th1_final>pi/2
        m = 1/tan(th1_final-pi/2);
    elseif th1_final<-pi/2
        m = 1/tan(th1_final+pi/2);
    end
    a = -m;
    b = 1;
    c = m*rung_pos(1)-rung_pos(2);
    
    gripper_position = gripper_pos(z, p);
    if (should_print)
%         gripper_position
    end
    x = (b*(b*gripper_position(1) - a*gripper_position(2))-a*c)/(a*a + b*b)-gripper_position(1);
    y = (a*(-b*gripper_position(1) + a*gripper_position(2))-b*c)/(a*a + b*b)-gripper_position(2);
    if (should_print)
%         x
%         y
    end
    gripper_velocity = gripper_vel(z, p);
    distance = sqrt(x^2+y^2);
    xUnit = x/distance;
    yUnit = y/distance;
    dDistance = gripper_velocity(1)*xUnit + gripper_velocity(2)*yUnit;
    
    K = 0.7;%10000;
    D = 0.06;%1000;
    
    F = (K*distance - D*dDistance)*[xUnit; yUnit];
    if (should_print)
%         F
    end
    J = gripper_jacobian(z, p);
    
    jointSp = J'*F;
    if (should_print)
%         jointSp
    end

    force = jointSp(2);
    
%     D = 10;
%     force = K*(th2_final-th2)-D*(dth2);
%     if (should_print)
%         force
%     end

end

