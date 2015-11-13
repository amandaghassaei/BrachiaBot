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
    K = 100;
    D = 10;
    th2_des = theta_desired(5*pi/6, th1, th2, dth1, dth2);
    
    v = K*(th2_des - th2) - D*dth2;% + k3*u_hat;
%     A_hat22 = 1;
    
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

function theta = theta_desired(range, th1, th2, dth1, dth2)

    num_turns = fix(th1/(2*pi));
    th1_rel = th1-num_turns*2*pi;
    theta = sign_nonzero(dth1)*(range-abs(th1_rel));%*cos(th1)
%     num_turns = fix(th2/(2*pi));
%     theta = theta + num_turns*2*pi;%shouldn't need this because theta2
%     should never pass PI

end

function mysign = sign_nonzero(val)

    mysign = sign(val);
    if mysign == 0
        mysign = 1;
    end

end