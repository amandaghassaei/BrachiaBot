function z0 = get_opt_z0(E, z_des, z, p)

    E_des = energy_brachia_bot(z_des, p);

    z0 = z(:,1);
    
    %find point in traj where 
    %E>E_des
    %th1 has opp sign as th1_des
    %dth1 is changing sign
    
    th1 = z(1, :);
    th2 = z(2, :);
    dth1 = z(3, :);
    dth2 = z(4, :);
    
%     index = find(E, E_des);
    
    
    

end

