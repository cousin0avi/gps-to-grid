addpath('lib')

%% Feed in lat and long
% phi    = 51.608131; %lat decimal degrees
% lambda =  0.053594; % long decimal degrees
% h = 19; %height m

prec_swch = '1';
d_m_s = 's';

phi = 52.658007833;
lambda = 1.716073973;
h = 108.05;

%% Convert lat-lon to OS GRID
[let_code,easting,northing] = gps2os([phi,lambda,h],prec_swch);


% 
% %% Convert OS GRID to lat-lon
% X = [str2double(easting),str2double(northing)];
% [lat,long] = os2gps(let_code,X,h,prec_swch);
% [ LAT,LONG ] = convert_dec_degree( [lat,long] ,prec_swch,d_m_s )
