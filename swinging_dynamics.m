function dz = swinging_dynamics(t, z, p)
        
    %soft limits on thetas
    

    % Get mass matrix
    A = A_brachia_bot(z,p);
    
    % Get angles
    th1 = z(1);
    th2 = z(2);
    
    % Get velocities
    dth1 = z(3);
    dth2 = z(4);
    
    % Forces
    F_th2 = theta_2_ang_constraint(th2, dth2);
    tau3 = -th1*0.5 + F_th2;
    u = [tau3];
    
    b = b_brachia_bot(z, u, p);
    
    % Solve for qdd
    qdd = A\b;
    dz = 0*z;
    
    % Form dz
    dz(1:2) = z(3:4);
    dz(3:4) = qdd;

end


function F_th2 = theta_2_ang_constraint(th2, dth2)

    %% Fixed parameters for contact 
    K_c = 1000;
    D_c = 20;
    
%     th3 = rem(th3, pi);
        
    if (dth2 > 0)
        
        %approaching counterclockwise
        th2C = pi-0.1;
        C = th2 - th2C;
        dC = dth2;

        F_th2 = -K_c*C - D_c*dC; 
        if (F_th2 > 0 || C < 0)
            F_th2 = 0; 
        end
        
    else 
        
        %approaching clockwise
        th2C = -(pi-0.1);
        C = -(th2 - th2C);
        dC = -dth2;

        F_th2 = -K_c*C - D_c*dC;
        if (F_th2 > 0 || C < 0)
            F_th2 = 0; 
        end
        F_th2 = -F_th2;
        
    end  
end


