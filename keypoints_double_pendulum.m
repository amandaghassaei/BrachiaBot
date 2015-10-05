function keypoints = keypoints_double_pendulum(in1,in2)
%KEYPOINTS_DOUBLE_PENDULUM
%    KEYPOINTS = KEYPOINTS_DOUBLE_PENDULUM(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 6.0.
%    05-Oct-2015 13:27:31

l1 = in2(1,:);
l2 = in2(2,:);
l3 = in2(3,:);
th1 = in1(1,:);
th2 = in1(2,:);
th3 = in1(3,:);
t2 = sin(th1);
t3 = l1.*t2;
t4 = th1+th2;
t5 = sin(t4);
t6 = l2.*t5;
t7 = cos(th1);
t8 = cos(t4);
t9 = th1+th2+th3;
keypoints = reshape([t3,-l1.*t7,t3+t6,-l1.*t7-l2.*t8,t3+t6+l3.*sin(t9),-l1.*t7-l2.*t8-l3.*cos(t9)],[2, 3]);
