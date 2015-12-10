function th_des = obstacle_th2(z, p, th_des_input)

    safe_rad = 0.07;
    th2_min_min = pi-2*asin((p(10)-safe_rad)/(2*p(1)));
    th2_min_max = pi-2*asin((p(10)*sqrt(2)-safe_rad)/(2*p(1)));
    
    th2_min_avg = (th2_min_min+th2_min_max)/2;
    th2_min_amp = (th2_min_min-th2_min_avg)/2;
    
    th1 = z(1);
    th2 = z(2);
    
    direction = 1;
    if th2<0
        direction = -1;
    end
    
    th2_min_phase = direction*th2_min_min;
    th2_min = th2_min_min+2*th2_min_amp*cos(4*(th1+th2_min_phase));

    th_des = th_des_input;
    
    if (direction*th_des < th2_min)
        th_des = direction*th2_min;
    end
end

