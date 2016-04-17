function [ lat,long,high ] = os2gps(let_code,OS,h,prec_swch ) %#codegen
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

source_tmp = os_tmp(); 

gps_ellip = gps_ellipsoid()
os_ellip = os_ellipsoid();

%% Convert letter grid to number grid
X = convert_os_letters_grid_number(let_code,OS,prec_swch);

%% Convert eastings and northings to lat-long
Y = zeros(1,3);

Y(1:2) = eastings_latlong(X,source_tmp,os_ellip);
Y(3) = h; %Needed for cart conversion
%% Convert lat-lon to cartesian
Z = latlong_cart(Y,os_ellip);

%% Transform to WGS84 ellipsoid
W = rotate_ellipsoid_to_gps(Z,'os',prec_swch);

%% Convert cartesian to lat-long
LL = cart_latlong(W,gps_ellip);

%Convert into degrees
lat = LL(1)*180/pi;
long = LL(2)*180/pi;
high = LL(3);
end

