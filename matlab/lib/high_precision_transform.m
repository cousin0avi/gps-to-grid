function [ Y,DY ] = high_precision_transform( X,swtch,rnd )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

e_idx = floor(X(1)/1000);
n_idx = floor(X(2)/1000);

X_0 = [e_idx n_idx]*1000;

switch swtch
    case 'os'
        idx0 =  e_idx    +  n_idx*701 + 1;
        [s0,s1,s2,s3] = find_ostn02_dat(idx0);
    otherwise
        error('Wrong flag')
end

t = (X(1) - X_0(1))/1000;
u = (X(1) - X_0(1))/1000;

se = (1-t)*(1-u)*s0(1) + t*(1-u)*s1(1) + t*u*s2(1) + (1-t)*u*s3(1);
sn = (1-t)*(1-u)*s0(2) + t*(1-u)*s1(2) + t*u*s2(2) + (1-t)*u*s3(2);
sg = (1-t)*(1-u)*s0(3) + t*(1-u)*s1(3) + t*u*s2(3) + (1-t)*u*s3(3);

DY = [se,sn,-sg];

E = X(1) + se;
N = X(2) + sn;
H = round(X(3) - sg);

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

Y = [E,N,H];


end

