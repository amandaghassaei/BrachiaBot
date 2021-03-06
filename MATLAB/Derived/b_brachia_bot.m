function b = b_brachia_bot(in1,in2,in3)
%B_BRACHIA_BOT
%    B = B_BRACHIA_BOT(IN1,IN2,IN3)

%    This function was generated by the Symbolic Math Toolbox version 6.0.
%    06-Dec-2015 01:36:51

c1 = in3(3,:);
c2 = in3(4,:);
dth1 = in1(3,:);
dth2 = in1(4,:);
g = in3(9,:);
l1 = in3(1,:);
m1 = in3(5,:);
m2 = in3(6,:);
tau1 = in2(1,:);
tau2 = in2(2,:);
th1 = in1(1,:);
th2 = in1(2,:);
t2 = sin(th2);
t3 = sin(th1);
t4 = th1+th2;
t5 = sin(t4);
b = [tau1+dth2.*(c2.*dth1.*l1.*m2.*t2.*2.0+c2.*dth2.*l1.*m2.*t2)-g.*m2.*(c2.*t5+l1.*t3)-c1.*g.*m1.*t3;tau2-c2.*g.*m2.*t5-c2.*dth1.^2.*l1.*m2.*t2];
