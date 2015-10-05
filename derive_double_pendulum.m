
%setup variables
syms rB rC theta1 theta2 dtheta1 dtheta2 ddtheta1 ddtheta2 t1 t2 I1 I2 l1 l2 c1 c2 m1 m2 g real
syms kappa1 kappa2 k3 theta1O theta2O rx ry lO real

% Group them
q   = [theta1; theta2];% generalized coordinates
dq  = [dtheta1; dtheta2];% first time derivatives
ddq = [ddtheta1; ddtheta2];% second time derivatives
u   = [t1; t2];% controls
p   = [m1; m2; I1; I2; l1; l2; c1; c2; g; kappa1; kappa2; k3; theta1O; theta2O; rx; ry; lO];% parameters

%unit vectors
khat = [0; 0; 1];
uhat = [sin(theta1); -cos(theta1); 0];%unit vector pointing along mass 1 from 0,0
vhat = [sin(theta1+theta2); -cos(theta1+theta2); 0];%unit vector pointing along mass 2 from B

ddt = @(r) jacobian(r, [q;dq])*[dq;ddq];%time derivatives

rB = l1*uhat;
rC = rB + l2*vhat;
cm1 = c1*uhat;
cm2 = rB + c2*vhat;

dB = ddt(rB);
dC = ddt(rC);
dcm1 = ddt(cm1);
dcm2 = ddt(cm2);

%kinetic energy
T1 = 1/2*m1*dot(dcm1, dcm1) + 1/2*I1*dtheta1^2;
T2 = 1/2*m2*dot(dcm2, dcm2) + 1/2*I2*(dtheta2^2 + dtheta1^2);
Ttotal = simplify(T1 + T2);

%potential energy
ihat = [0; 1; 0];
Vg1 = m1*g*dot(cm1, ihat);
Vg2 = m2*g*dot(cm2, ihat);
Ve1 = 1/2*kappa1*(theta1 - theta1O)^2;
Ve2 = 1/2*kappa2*(theta2 - theta2O)^2;
rO = [rx, ry, 0]';
Ve3 = 1/2*k3*(norm(rC - rO) - lO)^2;
Vtotal = simplify(Vg1 + Vg2);% + Ve1 + Ve2 + Ve3);

%forces
M2Q = @(M,w) simplify(jacobian(w,dq)'*(M));% moment contributions to generalized forces
Q_t1 = M2Q(t1*khat, dtheta1*khat);
Q_t2 = M2Q(t2*khat, dtheta2*khat);
Q = Q_t1 + Q_t2;

%derive eqs of motion
E = Ttotal + Vtotal;
L = Ttotal - Vtotal;
g = ddt(jacobian(L,dq).') - jacobian(L,q).' - Q;

%rearrange
A = jacobian(g,ddq);
b = A*ddq - g;

%write energy functions and eqs of motion
keypoints = [rB(1:2) rC(1:2)];
name = 'double_pendulum';
z  = [q ; dq];
matlabFunction(A,'file',['A_' name],'vars',{z p});
matlabFunction(b,'file',['b_' name],'vars',{z u p});
matlabFunction(E,'file',['energy_' name],'vars',{z p});
matlabFunction(keypoints,'file',['keypoints_' name],'vars',{z p});
matlabFunction(Vtotal,'file',['potential_' name],'vars',{theta1 theta2 p});