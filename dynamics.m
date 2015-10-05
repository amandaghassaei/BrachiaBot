function dz = dynamics(t, z, p)
    
    % Get mass matrix
    A = A_brachia_bot(z,p);
    
    % Get angles
    th1 = z(1);
    th2 = z(2);
    th3 = z(3);
    th4 = z(4);
    
    % Get velocities
    dth1 = z(5);
    dth2 = z(6);
    dth3 = z(7);
    dth4 = z(8);
    
    % Forces
    tau1 = 0;
    tau2 = 0;
    tau3 = 0;
    tau4 = 0;
    u = [tau1; tau2; tau3; tau4];
    
    b = b_brachia_bot(z, u, p);
    
    % Solve for qdd
    qdd = A\b;
    dz = 0*z;
    
    % Form dz
    dz(1:4) = z(5:8);
    dz(5:8) = qdd;

end