function [Y] = eastings_latlong( X,tmp,ellips)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

% Projection constants
F_0 = tmp(1);
phi_0 = tmp(2);
lambda_0 = tmp(3);
E_0 = tmp(4);
N_0 = tmp(5);

% Ellipsoid constants
e2 = ellips(1);
a = ellips(2);
b = ellips(3);

n = (a-b)/(a+b);

%%
phi_p = (X(2) - N_0)/(a*F_0) + phi_0;
diff = 1;

while diff>1e-9
    d_phi = phi_p-phi_0;
    s_phi = phi_p+phi_0;
    
    M = b*F_0*(...
    (1+n+5/4*n*n+5/4*n*n*n)*(d_phi) - ...
    (3*n+3*n*n +21/8*n*n*n)*sin(d_phi)*cos(s_phi) + ...
    (15/8*n*n + 15/8*n*n*n)*sin(2*d_phi)*cos(2*s_phi) - ...
    35/24*n*n*n*sin(3*d_phi)*cos(3*s_phi) );
    
    phi_p1 = (X(2) - N_0 - M)/(a*F_0) + phi_p;
    
    diff = abs(X(2) - N_0 - M);
    phi_p = phi_p1;
end

ome2sp = 1-e2*(sin(phi_p)^2);
nu = a*F_0/sqrt(ome2sp);
rho = a*F_0*(1-e2)*ome2sp^(-1.5);
eta2 = nu/rho - 1;

nu3 = nu * nu *nu;
nu5 = nu3*nu*nu;
nu7 = nu5*nu*nu;

tan_p = tan(phi_p);
tan2_p = tan_p*tan_p;
tan4_p = tan2_p*tan2_p;

sec_p = sec(phi_p);

vii = tan_p/(2*rho*nu);
viii = tan_p/(24*rho*nu3)*( 5+3*tan2_p + eta2 - 9*eta2*tan2_p);
ix = tan_p/(720*rho*nu5)*( 61 +90*tan2_p+45*tan4_p );
x = sec_p/nu;
xi = sec_p/(6*nu3)*( nu/rho + 2*tan2_p );
xii = sec_p/(120*nu5)*( 5+28*tan2_p+24*tan4_p );
xiia = sec_p/(5040*nu7)*( 61+662*tan2_p+1320*tan4_p+720*tan4_p*tan2_p );

E_diff = (X(1)-E_0);
E_diff_2 = E_diff*E_diff;
E_diff_3 = E_diff_2*E_diff;
E_diff_4 = E_diff_2*E_diff_2;

phi = phi_p - vii*E_diff_2 + viii*E_diff_4 - ix*E_diff_3*E_diff_3;
lambda = lambda_0 + x*E_diff - xi*E_diff_3 + xii*E_diff_2*E_diff_3 - xiia*E_diff_3*E_diff_4;

Y=[phi;lambda];

end

