function J = gripper_jacobian_brachia_bot(in1,in2)
%GRIPPER_JACOBIAN_BRACHIA_BOT
%    J = GRIPPER_JACOBIAN_BRACHIA_BOT(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 6.0.
%    13-Nov-2015 22:24:33

l1 = in2(1,:);
l2 = in2(2,:);
th1 = in1(1,:);
th2 = in1(2,:);
t2 = th1+th2;
t3 = cos(t2);
t4 = l2.*t3;
t5 = sin(t2);
t6 = l2.*t5;
J = reshape([t4+l1.*cos(th1),t6+l1.*sin(th1),t4,t6],[2, 2]);
