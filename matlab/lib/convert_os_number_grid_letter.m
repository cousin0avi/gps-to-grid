function [ os_code,eastings,northings ] = convert_os_number_grid_letter( OS,rnd ) %#codegen
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here
a = convertnum(OS(1),6);
b = convertnum(OS(2),7);

ii = str2double(a(1))+1;
jj = str2double(b(1:2))+1;
os_code = os_letter_code(ii,jj);

switch rnd
    case '100'
        eastings = a(2:4);
        northings = b(3:5);
    case '10'
        eastings = a(2:5);
        northings = b(3:6);
    case '1'
        eastings = a(2:6);
        northings = b(3:7);
    otherwise
        error('Wrong flag')
end

end

