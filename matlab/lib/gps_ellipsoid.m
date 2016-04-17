function [gps_e2,gps_a,gps_b] = gps_ellipsoid()


gps_a = 6378137.000;
gps_b = 6356752.3141;
gps_e2 = 1 - (gps_b/gps_a)^2;

end