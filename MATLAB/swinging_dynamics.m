function dz = swinging_dynamics(t, z, p)

    % Get mass matrix
    A = A_brachia_bot(z,p);

    tau = calc_tau(z, p);

    u = [0; tau];
    
    b = b_brachia_bot(z, u, p);
    
    % Solve for qdd
    qdd = A\b;
    dz = 0*z;
    
    % Form dz
    dz(1:2) = z(3:4);
    dz(3:4) = qdd;

end
