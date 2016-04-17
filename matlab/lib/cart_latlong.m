function [ X ] = cart_latlong( CC,ellips) %#codegen
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

% Ellipsoid constants
e2 = ellips(1);
a = ellips(2);

p = sqrt(CC(1)*CC(1) + CC(2)*CC(2));

lambda = atan(CC(2)/CC(1));

phi = atan(CC(3)/(p*(1-e2)));
check = 1;
nu = 0;

while check > eps
    nu = a/(sqrt(1-e2*(sin(phi)^2)));
    phi1 = atan( (CC(3) + e2*nu*sin(phi))/p );
    check = abs(phi1-phi)/phi;
    phi = phi1;
end

h = p/cos(phi) - nu;

X = [phi, lambda, h];

end

