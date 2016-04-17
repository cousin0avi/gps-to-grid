function [ code ] = os_letter_code( ii,jj )
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here

os_lm = os_letter_matrix;

code = os_lm{jj,ii};
    
end

