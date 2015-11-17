function force = obstacle_avoidance(z, p)

    % Get angles
    th1 = z(1);
    th2 = z(2);
    
    % Get velocities
    dth1 = z(3);
    dth2 = z(4);

    force = 0;
    
    pitch = p(10);
    
%     r_gripper = gripper_pos(z,p);
%     
%     
%     K = 100;
%     D = 50;
% 
%     for i=-1:1
%         for j=-1:1
%             rung_pos = [i*pitch; j*pitch; 0];
%             distance = norm(r_gripper - rung_pos);
%             force = force + sign(th2)*(K*(1/distance)^2-D*dth2);
%         end
%     end
end

