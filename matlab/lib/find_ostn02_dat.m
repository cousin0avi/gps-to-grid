function [ s0,s1,s2,s3 ] = find_ostn02_dat(idx0)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

fid = fopen('ostn02.dat');

a = textscan(fid,'%f%f%f',2,'Delimiter',',','EndOfLine','\n','HeaderLines',idx0-1);
b = textscan(fid,'%f%f%f',2,'Delimiter',',','EndOfLine','\n','HeaderLines',700);

fclose(fid);

s0 = zeros(1,3);
s1 = s0;
s2 = s0;
s3 = s0;

for ii=1:3
    s0(ii) = a{ii}(1);
    s1(ii) = a{ii}(2);
    s2(ii) = b{ii}(1);
    s3(ii) = b{ii}(2);
end

end

