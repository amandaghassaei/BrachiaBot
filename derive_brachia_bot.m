
%setup variables
syms th1 th2 th3 th4 dth1 dth2 dth3 dth4 ddth1 ddth2 ddth3 ddth4 real
syms m1 m2 m3 m4 I1 I2 I3 I4 g real
syms l1 l2 l3 l4 c1 c2 c3 c4 r_B r_C r_D r_E real
syms tau1 tau2 tau3 tau4 real

% Group them
q   = [th1; th2; th3; th4];% generalized coordinates
dq  = [dth1; dth2; dth3; dth4];% first time derivatives
ddq = [ddth1; ddth2; ddth3; ddth4];% second time derivatives
u   = [tau1; tau2; tau3; tau4];% controls
p   = [l1; l2; l3; l4; c1; c2; c3; c4; m1; m2; m3; m4; I1; I2; I3; I4; g];% parameters

%unit vectors
xhat = [1; 0; 0];
yhat = [0; 1; 0];
zhat = [0; 0; 1];
uhat = [sin(th1); -cos(th1); 0];%unit vector pointing along mass 1 from 0,0
vhat = [sin(th1+th2); -cos(th1+th2); 0];%unit vector pointing along mass 2 from B
what = [sin(th1+th2+th3); -cos(th1+th2+th3); 0];%unit vector pointing along mass 3 from C
ihat = [sin(th1+th2+th3+th4); -cos(th1+th2+th3+th4); 0];%unit vector pointing along mass 4 from D

ddt = @(r) jacobian(r, [q;dq])*[dq;ddq];%time derivatives

r_B = l1*uhat;
r_C = r_B + l2*vhat;
r_D = r_C + l3*what;
r_E = r_D + l4*ihat;
r_m1 = c1*uhat;
r_m2 = r_B + c2*vhat;
r_m3 = r_C + c3*what;
r_m4 = r_D + c4*ihat;

dr_B = ddt(r_B);
dr_C = ddt(r_C);
dr_D = ddt(r_D);
dr_E = ddt(r_E);
dr_m1 = ddt(r_m1);
dr_m2 = ddt(r_m2);
dr_m3 = ddt(r_m3);
dr_m4 = ddt(r_m4);

%kinetic energy
T1 = 1/2*m1*dot(dr_m1, dr_m1) + 1/2*I1*dth1^2;
T2 = 1/2*m2*dot(dr_m2, dr_m2) + 1/2*I2*(dth1^2 + dth2^2);
T3 = 1/2*m3*dot(dr_m3, dr_m3) + 1/2*I3*(dth1^2 + dth2^2 + dth3^2);
T4 = 1/2*m4*dot(dr_m4, dr_m4) + 1/2*I4*(dth1^2 + dth2^2 + dth3^2 + dth4^2);
Ttotal = simplify(T1 + T2 + T3 + T4);

%potential energy
Vg1 = m1*g*dot(r_m1, yhat);
Vg2 = m2*g*dot(r_m2, yhat);
Vg3 = m3*g*dot(r_m3, yhat);
Vg4 = m4*g*dot(r_m4, yhat);
Vtotal = simplify(Vg1 + Vg2 + Vg3 + Vg4);

%forces
M2Q = @(M,w) simplify(jacobian(w,dq)'*(M));% moment contributions to generalized forces
Q_tau1 = M2Q(tau1*zhat, dth1*zhat);
Q_tau2 = M2Q(tau2*zhat, dth2*zhat);
Q_tau3 = M2Q(tau3*zhat, dth3*zhat);
Q_tau4 = M2Q(tau4*zhat, dth4*zhat);
Q = Q_tau1 + Q_tau2 + Q_tau3 + Q_tau4;

%derive eqs of motion
E = Ttotal + Vtotal;
L = Ttotal - Vtotal;
g = ddt(jacobian(L,dq).') - jacobian(L,q).' - Q;

%rearrange
A = jacobian(g,ddq);
b = A*ddq - g;

%write energy functions and eqs of motion
keypoints = [r_B(1:2) r_C(1:2) r_D(1:2) r_E(1:2)];
name = 'brachia_bot';
z  = [q ; dq];
matlabFunction(A,'file',['A_' name],'vars',{z p});
matlabFunction(b,'file',['b_' name],'vars',{z u p});
matlabFunction(E,'file',['energy_' name],'vars',{z p});
matlabFunction(keypoints,'file',['keypoints_' name],'vars',{z p});
% matlabFunction(Vtotal,'file',['potential_' name],'vars',{th1 th2 p});