function dz = dynamics(t, z, p, options)
    
    if options.fixed_wrist
        z = fix_wrist(z);
    end

    % Get mass matrix
    A = A_brachia_bot(z,p);
    
    % Get angles
    th1 = z(1);
    th2 = z(2);
    
    % Get velocities
    dth1 = z(5);
    dth2 = z(6);
    
    % Forces
    tau = 0;
    u = [tau];
    
    b = b_brachia_bot(z, u, p);
    
    % Solve for qdd
    qdd = A\b;
    dz = 0*z;
    
    % Form dz
    dz(1:2) = z(3:4);
    dz(3:4) = qdd;

end
