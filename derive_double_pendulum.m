
%setup variables
syms t th1 th2 dth1 dth2 ddth1 ddth2 real
syms m1 m2 m3 m4 I1 I2 I3 I4 l_O_m1 l_B_m2 l_A_m3 l_C_m4  g real
syms l_OA l_OB l_AC l_DE real 
syms tau1 tau2 Fx Fy real

syms th1 th2 dth1 dth2 ddth1 ddth2 real
syms m1 m2 I1 I2 g real
syms l1 l2 c1 c2 r_B r_C real
syms tau1 tau2 real

syms rB rC theta1 theta2 dtheta1 dtheta2 ddtheta1 ddtheta2 t1 t2 I1 I2 l1 l2 c1 c2 m1 m2 g real
syms kappa1 kappa2 k3 theta1O theta2O rx ry lO real

% Group them
q   = [th1; th2];% generalized coordinates
dq  = [dth1; dth2];% first time derivatives
ddq = [ddth1; ddth2];% second time derivatives
u   = [tau1; tau2];% controls
p   = [l1; l2; c1; c2; m1; m2; I1; I2; g];% parameters

%unit vectors
ihat = [0; 1; 0];
uhat = [sin(th1); -cos(th1); 0];%unit vector pointing along mass 1 from 0,0
vhat = [sin(th1+th2); -cos(th1+th2); 0];%unit vector pointing along mass 2 from B
khat = [0; 0; 1];

ddt = @(r) jacobian(r, [q;dq])*[dq;ddq];%time derivatives

r_B = l1*uhat;
r_C = r_B + l2*vhat;
r_m1 = c1*uhat;
r_m2 = r_B + c2*vhat;

dr_B = ddt(rB);
dr_C = ddt(rC);
dr_m1 = ddt(r_m1);
dr_m2 = ddt(r_m2);

%kinetic energy
T1 = 1/2*m1*dot(dr_m1, dr_m1) + 1/2*I1*dth1^2;
T2 = 1/2*m2*dot(dr_m2, dr_m2) + 1/2*I2*(dth2^2 + dth1^2);
Ttotal = simplify(T1 + T2);

%potential energy
Vg1 = m1*g*dot(r_m1, ihat);
Vg2 = m2*g*dot(r_m2, ihat);
Vtotal = simplify(Vg1 + Vg2);

%forces
M2Q = @(M,w) simplify(jacobian(w,dq)'*(M));% moment contributions to generalized forces
Q_tau1 = M2Q(tau1*khat, dth1*khat);
Q_tau2 = M2Q(tau2*khat, dth2*khat);
Q = Q_tau1 + Q_tau2;

%derive eqs of motion
E = Ttotal + Vtotal;
L = Ttotal - Vtotal;
g = ddt(jacobian(L,dq).') - jacobian(L,q).' - Q;

%rearrange
A = jacobian(g,ddq);
b = A*ddq - g;

%write energy functions and eqs of motion
keypoints = [r_B(1:2) r_C(1:2)];
name = 'double_pendulum';
z  = [q ; dq];
matlabFunction(A,'file',['A_' name],'vars',{z p});
matlabFunction(b,'file',['b_' name],'vars',{z u p});
matlabFunction(E,'file',['energy_' name],'vars',{z p});
matlabFunction(keypoints,'file',['keypoints_' name],'vars',{z p});
matlabFunction(Vtotal,'file',['potential_' name],'vars',{th1 th2 p});