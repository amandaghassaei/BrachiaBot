function r_C = gripper_pos_brachia_bot(in1,in2)
%GRIPPER_POS_BRACHIA_BOT
%    R_C = GRIPPER_POS_BRACHIA_BOT(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 6.0.
%    13-Nov-2015 22:24:33

l1 = in2(1,:);
l2 = in2(2,:);
th1 = in1(1,:);
th2 = in1(2,:);
t2 = th1+th2;
r_C = [l2.*sin(t2)+l1.*sin(th1);-l2.*cos(t2)-l1.*cos(th1);0.0];