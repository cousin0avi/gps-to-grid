function [ X ] = latlong_eastings( LL,tmp,ellips,rnd ) %#codegen
%UNTITLED4 Summary of this function goes here
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


ome2sp = 1-e2*(sin(LL(1))^2);

d_long = LL(2) - lambda_0;
d_long2 = d_long*d_long;
d_long4 = d_long2*d_long2;

d_phi = LL(1)-phi_0;
s_phi = LL(1)+phi_0;

n = (a-b)/(a+b);
nu = a*F_0/sqrt(ome2sp);
rho = a*F_0*(1-e2)*ome2sp^(-1.5);
eta2 = nu/rho - 1;

M = b*F_0*(...
    (1+n+5/4*n*n+5/4*n*n*n)*(d_phi) - ...
    (3*n+3*n*n +21/8*n*n*n)*sin(d_phi)*cos(s_phi) + ...
    (15/8*n*n + 15/8*n*n*n)*sin(2*d_phi)*cos(2*s_phi) - ...
    35/24*n*n*n*sin(3*d_phi)*cos(3*s_phi) );

cos_lat = cos(LL(1));
sin_lat = sin(LL(1));
tan_lat_2 = tan(LL(1))*tan(LL(1));
cos_lat_3 = cos_lat*cos_lat*cos_lat;
cos_lat_5 = cos_lat_3*cos_lat*cos_lat;

i1 = M + N_0;
ii = nu/2*sin_lat*cos_lat;
iii = nu/24*sin_lat*cos_lat_3*(5-tan_lat_2+9*eta2);
iiia = nu/720*sin_lat*cos_lat_5*(61 - 58*tan_lat_2+tan_lat_2*tan_lat_2 );
iv = nu*cos_lat;
v = nu/6*cos_lat_3*(nu/rho - tan_lat_2);
vi = nu/120*cos_lat_5*( 5-18*tan_lat_2+tan_lat_2*tan_lat_2+14*eta2-58*eta2*tan_lat_2 );

N = i1 + (ii + iii*d_long2 + iiia*d_long4)*d_long2;
E = E_0 + (iv + v*d_long2 + vi*d_long4)*d_long;

switch rnd
    case '100'
        N = round(N/100)*100;
        E = round(E/100)*100;
    case '10'
        N = round(N/10)*10;
        E = round(E/10)*10;
    case '1'
        N = round(N);
        E = round(E);
    case '0'
        
    otherwise
        error('Wrong flag')
end

X = [E, N];
end

