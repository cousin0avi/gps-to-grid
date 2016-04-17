function [ Y ] = convert_os_letters_grid_number( let_code,X,rnd )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here


os_lm = os_letter_matrix;

idx = strcmp(os_lm,let_code);

[n_idx,e_idx] = find(idx);

switch rnd
    case '100'
        N = 1e5*(n_idx-1)+X(2)*100;
        E = 1e5*(e_idx-1)+X(1)*100;
    case '10'
        N = 1e5*(n_idx-1)+X(2)*10;
        E = 1e5*(e_idx-1)+X(1)*10;
    case '1'
        N = 1e5*(n_idx-1)+X(2);
        E = 1e5*(e_idx-1)+X(1);
    otherwise
        error('Wrong flag')
end

Y = [E, N];

end

