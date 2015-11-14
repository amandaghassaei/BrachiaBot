
%setup variables
syms th1 th2 dth1 dth2 ddth1 ddth2 real
syms m1 m2 I1 I2 g real
syms l1 l2 c1 c2 r_B r_C real
syms tau1 tau2 real

% Group them
q   = [th1; th2];% generalized coordinates
dq  = [dth1; dth2];% first time derivatives
ddq = [ddth1; ddth2];% second time derivatives
u   = [tau1; tau2];% controls
p   = [l1; l2; c1; c2; m1; m2; I1; I2; g];% parameters

%unit vectors
xhat = [1; 0; 0];
yhat = [0; 1; 0];
zhat = [0; 0; 1];
uhat = [sin(th1); -cos(th1); 0];%unit vector pointing along mass 1
vhat = [sin(th1+th2); -cos(th1+th2); 0];%unit vector pointing along mass 2

ddt = @(r) jacobian(r, [q;dq])*[dq;ddq];%time derivatives

r_B = l1*uhat;
r_C = r_B + l2*vhat;
r_m1 = c1*uhat;
r_m2 = r_B + c2*vhat;

dr_B = ddt(r_B);
dr_C = ddt(r_C);
dr_m1 = ddt(r_m1);
dr_m2 = ddt(r_m2);

%kinetic energy
T1 = 1/2*m1*dot(dr_m1, dr_m1) + 1/2*I1*dth1^2;
% ??????   1/2*I2*(dth1 + dth2)^2 or 1/2*I2*(dth1^2 + dth2^2) ???????
T2 = 1/2*m2*dot(dr_m2, dr_m2) + 1/2*I2*(dth1^2 + dth2^2);
Ttotal = simplify(T1 + T2);

%potential energy
Vg1 = m1*g*dot(r_m1, yhat);
Vg2 = m2*g*dot(r_m2, yhat);
Vtotal = simplify(Vg1 + Vg2);

%forces
M2Q = @(M,w) simplify(jacobian(w,dq)'*(M));% moment contributions to generalized forces
Q_tau1 = M2Q(tau1*zhat, dth1*zhat);
Q_tau2 = M2Q(tau2*zhat, dth2*zhat);
Q = Q_tau1 + Q_tau2;

%derive eqs of motion
E = Ttotal + Vtotal;
L = Ttotal - Vtotal;
eom = ddt(jacobian(L,dq).') - jacobian(L,q).' - Q;

%rearrange
A = jacobian(eom,ddq);
b = A*ddq - eom;

% Equations of motion are
% eom = A *ddq + (coriolis term) + (gravitational term) - Q = 0
Mass_Joint_Sp = A;
Grav_Joint_Sp = simplify(jacobian(Vtotal, q)');
Corr_Joint_Sp = simplify( eom + Q - Grav_Joint_Sp - A*ddq);

%write energy functions and eqs of motion
keypoints = [r_B(1:2) r_C(1:2)];
name = 'brachia_bot';
z  = [q ; dq];
matlabFunction(A,'file',['A_' name],'vars',{z p});
matlabFunction(b,'file',['b_' name],'vars',{z u p});
matlabFunction(E,'file',['energy_' name],'vars',{z p});
matlabFunction(keypoints,'file',['keypoints_' name],'vars',{z p});
matlabFunction(r_C ,'file', ['gripper_pos' name],'vars',{z p});
matlabFunction(dr_C ,'file', ['gripper_vel' name],'vars',{z p});

matlabFunction(Grav_Joint_Sp ,'file', ['Grav_' name] ,'vars',{z p});
matlabFunction(Corr_Joint_Sp ,'file', ['Corr_' name]     ,'vars',{z p});