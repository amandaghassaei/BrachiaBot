function dr_C = gripper_vel(in1,in2)
%GRIPPER_VEL
%    DR_C = GRIPPER_VEL(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 6.0.
%    05-Dec-2015 20:05:52

dth1 = in1(3,:);
dth2 = in1(4,:);
l1 = in2(1,:);
l2 = in2(2,:);
th1 = in1(1,:);
th2 = in1(2,:);
t2 = th1+th2;
t3 = cos(t2);
t4 = sin(t2);
dr_C = [dth1.*(l2.*t3+l1.*cos(th1))+dth2.*l2.*t3;dth1.*(l2.*t4+l1.*sin(th1))+dth2.*l2.*t4;0.0];
