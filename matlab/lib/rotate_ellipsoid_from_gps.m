function [ Y ] = rotate_ellipsoid_from_gps( X,swtch,rnd  ) %#codegen
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here

if (strcmp('100',rnd)||strcmp('10',rnd)) 
        
        switch swtch
            case 'os'
                tx = -446.448;
                ty = +125.157;
                tz = -542.060;
                
                rx = -0.1502 * 4.8481368e-6;
                ry = -0.2470 * 4.8481368e-6;
                rz = -0.8421 * 4.8481368e-6;
                
                s = +20.4894 * 1e-6;
            otherwise
                error('Wrong flag')
        end
        
        T = [tx;ty;tz];
        
        R = [1+s -rz ry;...
            rz 1+s -rx;...
            -ry rx 1+s];
        
        Y = T + R*X;
        
elseif strcmp('1',rnd)
        error('1m precision is not functional yet')
else
        error('Wrong flag')
end

end

