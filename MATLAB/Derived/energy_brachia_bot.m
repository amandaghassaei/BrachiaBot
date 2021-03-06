function E = energy_brachia_bot(in1,in2)
%ENERGY_BRACHIA_BOT
%    E = ENERGY_BRACHIA_BOT(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 6.0.
%    06-Dec-2015 01:36:51

I1 = in2(7,:);
I2 = in2(8,:);
c1 = in2(3,:);
c2 = in2(4,:);
dth1 = in1(3,:);
dth2 = in1(4,:);
g = in2(9,:);
l1 = in2(1,:);
m1 = in2(5,:);
m2 = in2(6,:);
th1 = in1(1,:);
th2 = in1(2,:);
t2 = dth1.^2;
t3 = c2.^2;
t4 = dth2.^2;
t5 = cos(th1);
t6 = cos(th2);
E = I1.*t2.*(1.0./2.0)+I2.*t2.*(1.0./2.0)+I2.*t4.*(1.0./2.0)+c1.^2.*m1.*t2.*(1.0./2.0)+l1.^2.*m2.*t2.*(1.0./2.0)-g.*m2.*(l1.*t5+c2.*cos(th1+th2))+m2.*t2.*t3.*(1.0./2.0)+m2.*t3.*t4.*(1.0./2.0)+dth1.*dth2.*m2.*t3-c1.*g.*m1.*t5+c2.*l1.*m2.*t2.*t6+c2.*dth1.*dth2.*l1.*m2.*t6;
