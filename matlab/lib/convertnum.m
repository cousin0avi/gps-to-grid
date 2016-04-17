function [ s ] = convertnum(n,b)
%UNTITLED10 Summary of this function goes here
%   Detailed explanation goes here

a = floor(log10(abs(n)+1)) + 1;

assert(b>=a,'Error when converting num2str')

s = repmat('0',1,b);

for ii=b:-1:(b-a+1)
    d = mod(n,10);
    s(ii) = char(48+d);
    n = (n-d)/10;
end
end


