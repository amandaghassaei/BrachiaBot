function dz = swinging_dynamics(t, z, p, E_des)
        
    % Get mass matrix
    A = A_brachia_bot(z,p);
    
    % Get angles
    th1 = z(1);
    th2 = z(2);
    
    % Get velocities
    dth1 = z(3);
    dth2 = z(4);
        
    % Forces
    E = energy_brachia_bot(z, p);
    
    A_hat22 = A(2,2)-A(2,1)*A(1,2)/A(1,1);
    range = pi/2;
    K = 100;
    D = 10;
%     th2_des = range;
%     if dth1>0.1 || th2>0.25
        th2_des = range*sign(dth1);
%     end
    v = K*(th2_des - th2) - D*dth2;% + k3*u_hat;
    
    % Compute virtual foce
%     lambda = A*J_inv

    rho = Grav_brachia_bot(z, p);
    rho = rho(2);
    
    %todo coriolis/cetripedal compensation, desired accel?
%     mu = Corr_brachia_bot(z, p) - lambda*jacobian_dth2_brachia_bot(z,p)*dth2;
%     mu = mu(2);
    
    tau = A_hat22*v + rho;
    u = [0; tau];
    
    b = b_brachia_bot(z, u, p);
    
    % Solve for qdd
    qdd = A\b;
    dz = 0*z;
    
    % Form dz
    dz(1:2) = z(3:4);
    dz(3:4) = qdd;

end