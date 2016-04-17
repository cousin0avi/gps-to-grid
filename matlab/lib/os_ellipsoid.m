function [os_e2,os_a,os_b] = os_ellipsoid()


os_a = 6377563.396;
os_b = 6356256.909;
os_e2 = 1 - (os_b/os_a)^2;

end