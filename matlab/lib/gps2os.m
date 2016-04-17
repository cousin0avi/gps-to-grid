function [ let_code,easting,northing ] = gps2os( LL,prec_swch ) %#codegen
%gps2os Coverts Lat-Long from GPS to an OS grid ref
%   Detailed explanation goes here

target_tmp = os_tmp(); 

gps_ellip = gps_ellipsoid();
os_ellip = os_ellipsoid();

%Convert into radians
LL(1) = LL(1)*pi/180;
LL(2) = LL(2)*pi/180;

% Save height data
h = LL(3); 
%% If 1m precision is required use OSGM02 otherwise use helmert datum transformation
if strcmp(prec_swch,'1')    
    % Convert lat-long to eastings and northings
    X = latlong_eastings(LL,target_tmp,gps_ellip,'0');
    
    % Transform gps eastings and northings to os eastings and northings
    Z = high_precision_transform([X,h],'os',prec_swch);
else
    % Convert lat-lon to cartesian
    W = latlong_cart(LL,gps_ellip);
    
    % Transform to Airy 1830 ellipsoid
    X = rotate_ellipsoid_from_gps(W,'os',prec_swch);
    
    % Convert cartesian into lat-long
    Y = cart_latlong(X,os_ellip);
    
    % Convert lat-long to eastings and northings
    Z = latlong_eastings(Y,target_tmp,os_ellip,prec_swch);
end
%% Convert number grid to letter grid
[let_code,easting,northing] = convert_os_number_grid_letter(Z,prec_swch);
end

