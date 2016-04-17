function [ X ] = latlong_cart(LL,ellips) %#codegen
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

% Ellipsoid constants
e2 = ellips(1);
a = ellips(2);

nu = a/(sqrt(1-e2*(sin(LL(1))^2)));

X = [(nu + LL(3))*cos(LL(1))*cos(LL(2));...
     (nu + LL(3))*cos(LL(1))*sin(LL(2));...
     ((1-e2)*nu + LL(3))*sin(LL(1))];


end