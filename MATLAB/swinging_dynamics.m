function dz = swinging_dynamics(t, z, p)

    % Get mass matrix
    A = A_brachia_bot(z,p);

    tau = calc_tau(z, p, t);

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
%     if abs(th1_rel) > pi
%         th1_rel  = sign(th1_rel)*(abs(th1_rel)-pi);
%     end
    
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