function keypoints = keypoints_brachia_bot(in1,in2)
%KEYPOINTS_BRACHIA_BOT
%    KEYPOINTS = KEYPOINTS_BRACHIA_BOT(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 6.0.
%    05-Dec-2015 20:05:52

l1 = in2(1,:);
l2 = in2(2,:);
th1 = in1(1,:);
th2 = in1(2,:);
t2 = sin(th1);
t3 = l1.*t2;
t4 = th1+th2;
t5 = cos(th1);
keypoints = reshape([t3,-l1.*t5,t3+l2.*sin(t4),-l1.*t5-l2.*cos(t4)],[2, 2]);
