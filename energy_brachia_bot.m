function E = energy_brachia_bot(in1,in2)
%ENERGY_BRACHIA_BOT
%    E = ENERGY_BRACHIA_BOT(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 6.0.
%    05-Oct-2015 13:43:30

I1 = in2(13,:);
I2 = in2(14,:);
I3 = in2(15,:);
I4 = in2(16,:);
c1 = in2(5,:);
c2 = in2(6,:);
c3 = in2(7,:);
c4 = in2(8,:);
dth1 = in1(5,:);
dth2 = in1(6,:);
dth3 = in1(7,:);
dth4 = in1(8,:);
g = in2(17,:);
l1 = in2(1,:);
l2 = in2(2,:);
l3 = in2(3,:);
m1 = in2(9,:);
m2 = in2(10,:);
m3 = in2(11,:);
m4 = in2(12,:);
th1 = in1(1,:);
th2 = in1(2,:);
th3 = in1(3,:);
th4 = in1(4,:);
t2 = th1+th2+th3+th4;
t3 = cos(t2);
t4 = c4.*t3;
t5 = th1+th2+th3;
t6 = cos(t5);
t7 = l3.*t6;
t8 = th1+th2;
t9 = cos(t8);
t10 = l2.*t9;
t22 = cos(th1);
t28 = l1.*t22;
t36 = t4+t7+t10+t28;
t11 = dth3.*(t4+t7)+dth1.*t36+dth2.*(t4+t7+t10)+c4.*dth4.*t3;
t12 = sin(t2);
t13 = c4.*t12;
t14 = sin(t5);
t15 = l3.*t14;
t16 = sin(t8);
t17 = l2.*t16;
t24 = sin(th1);
t25 = l1.*t24;
t18 = dth3.*(t13+t15)+dth2.*(t13+t15+t17)+dth1.*(t13+t15+t17+t25)+c4.*dth4.*t12;
t19 = dth1.^2;
t20 = dth2.^2;
t21 = dth3.^2;
t23 = c1.^2;
t26 = c3.*t14;
t27 = dth2.*(t17+t26)+dth1.*(t17+t25+t26)+c3.*dth3.*t14;
t29 = c3.*t6;
t33 = t10+t28+t29;
t30 = dth2.*(t10+t29)+dth1.*t33+c3.*dth3.*t6;
t34 = c2.*t9;
t35 = t28+t34;
t31 = dth1.*t35+c2.*dth2.*t9;
t32 = dth1.*(t25+c2.*t16)+c2.*dth2.*t16;
E = I1.*t19.*(1.0./2.0)+I4.*(t19+t20+t21+dth4.^2).*(1.0./2.0)+m1.*(t19.*t22.^2.*t23+t19.*t23.*t24.^2).*(1.0./2.0)+I3.*(t19+t20+t21).*(1.0./2.0)+m4.*(t11.^2+t18.^2).*(1.0./2.0)+m3.*(t27.^2+t30.^2).*(1.0./2.0)+m2.*(t31.^2+t32.^2).*(1.0./2.0)+I2.*(t19+t20).*(1.0./2.0)-g.*m3.*t33-g.*m2.*t35-g.*m4.*t36-c1.*g.*m1.*t22;