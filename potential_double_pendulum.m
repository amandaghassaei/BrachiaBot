function Vtotal = potential_double_pendulum(th1,th2,in3)
%POTENTIAL_DOUBLE_PENDULUM
%    VTOTAL = POTENTIAL_DOUBLE_PENDULUM(TH1,TH2,IN3)

%    This function was generated by the Symbolic Math Toolbox version 6.0.
%    05-Oct-2015 13:13:03

c1 = in3(3,:);
c2 = in3(4,:);
g = in3(9,:);
l1 = in3(1,:);
m1 = in3(5,:);
m2 = in3(6,:);
t2 = cos(th1);
Vtotal = -g.*m2.*(l1.*t2+c2.*cos(th1+th2))-c1.*g.*m1.*t2;
