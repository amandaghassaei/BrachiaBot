function dz = swinging_dynamics(t, z, p, options)
    
    z = fix_wrist(z);
    
    %soft limits on thetas
    

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
    F_th3 = theta_3_ang_constraint(th3, dth3);
    tau3 = -th1*0.5 + F_th3;
    u = [0; 0; tau3; 0];
    
    b = b_brachia_bot(z, u, p);
    
    % Solve for qdd
    qdd = A\b;
    dz = 0*z;
    
    % Form dz
    dz(1:4) = z(5:8);
    dz(5:8) = qdd;

end


function F_th3 = theta_3_ang_constraint(th3, dth3)

    %% Fixed parameters for contact 
    K_c = 1000;
    D_c = 20;
    
%     th3 = rem(th3, pi);
        
    if (dth3 > 0)
        
        %approaching counterclockwise
        th3C = pi-0.1;
        C = th3 - th3C;
        dC = dth3;

        F_th3 = -K_c*C - D_c*dC; 
        if (F_th3 > 0 || C < 0)
            F_th3 = 0; 
        end
        
    else 
        
        %approaching clockwise
        th3C = -(pi-0.1);
        C = -(th3 - th3C);
        dC = -dth3;

        F_th3 = -K_c*C - D_c*dC;
        if (F_th3 > 0 || C < 0)
            F_th3 = 0; 
        end
        F_th3 = -F_th3;
        
    end  
end


