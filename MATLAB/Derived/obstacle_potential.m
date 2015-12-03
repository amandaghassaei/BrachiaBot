function obstacle_potential = obstacle_potential(in1,in2)
%OBSTACLE_POTENTIAL
%    OBSTACLE_POTENTIAL = OBSTACLE_POTENTIAL(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 6.0.
%    03-Dec-2015 17:55:56

l1 = in2(1,:);
l2 = in2(2,:);
pitch = in2(10,:);
th1 = in1(1,:);
th2 = in1(2,:);
t3 = th1+th2;
t5 = cos(t3);
t6 = l2.*t5;
t7 = cos(th1);
t8 = l1.*t7;
t9 = pitch+t6+t8;
t2 = abs(t9);
t11 = sin(t3);
t12 = l2.*t11;
t13 = sin(th1);
t14 = l1.*t13;
t16 = pitch+t12+t14;
t4 = abs(t16);
t10 = t2.^2;
t15 = t12+t14;
t17 = t4.^2;
t18 = t6+t8;
t21 = -pitch+t6+t8;
t19 = abs(t21);
t24 = -pitch+t12+t14;
t20 = abs(t24);
t22 = t19.^2;
t23 = t15.^2;
t25 = t20.^2;
t26 = t18.^2;
obstacle_potential = 1.0./(t10+t17)+1.0./(t10+t23)+1.0./(t10+t25)+1.0./(t17+t22)+1.0./(t17+t26)+1.0./(t22+t23)+1.0./(t22+t25)+1.0./(t25+t26);
