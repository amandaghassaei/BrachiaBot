function A = A_brachia_bot(in1,in2)
%A_BRACHIA_BOT
%    A = A_BRACHIA_BOT(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 6.0.
%    06-Dec-2015 01:36:50

I1 = in2(7,:);
I2 = in2(8,:);
c1 = in2(3,:);
c2 = in2(4,:);
l1 = in2(1,:);
m1 = in2(5,:);
m2 = in2(6,:);
th2 = in1(2,:);
t2 = c2.^2;
t3 = m2.*t2;
t4 = cos(th2);
t5 = c2.*l1.*m2.*t4;
t6 = t3+t5;
A = reshape([I1+I2+t3+c1.^2.*m1+l1.^2.*m2+c2.*l1.*m2.*t4.*2.0,t6,t6,I2+t3],[2, 2]);
