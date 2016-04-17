function [ LAT,LONG ] = convert_dec_degree( X ,rnd,d_m_s ) %#codgen
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

switch d_m_s
    case 'd'
        switch rnd
            case '100'
                LAT = round(X(1)*1000)./1000;
                LONG = round(X(2)*1000)./1000;
            case '10'
                LAT = round(X(1)*10000)./10000;
                LONG = round(X(2)*10000)./10000;
            case '1'
                LAT = round(X(1)*100000)./100000;
                LONG = round(X(2)*100000)./100000;
            otherwise
                error('Wrong flag')
        end
    case 'm'
        LAT = zeros(2,1);
        LONG = LAT;
        
        LAT(1) = floor(X(1));
        LONG(1) = floor(X(2));
        
        LAT(2) = (X(1) - LAT(1))*60;
        LONG(2) = (X(2) - LONG(1))*60;
        
        switch rnd
            case '100'
                LAT(2) = round(LAT(2)*100)/100;
                LONG(2) = round(LONG(2)*100)/100;
            case '10'
                LAT(2) = round(LAT(2)*1000)/1000;
                LONG(2) = round(LONG(2)*1000)/1000;
            case '1'
                LAT(2) = round(LAT(2)*10000)/10000;
                LONG(2) = round(LONG(2)*10000)/10000;
            otherwise
                error('Wrong flag')
        end
        
    case 's'
        LAT = zeros(3,1);
        LONG = LAT;
        
        LAT(1) = floor(X(1));
        LONG(1) = floor(X(2));
        
        X(1) = (X(1) - LAT(1))*60;
        X(2) = (X(2) - LONG(1))*60;
        
        LAT(2) = floor(X(1));
        LONG(2) = floor(X(2));
        
        LAT(3) = (X(1) - LAT(2))*60;
        LONG(3) = (X(2) - LONG(2))*60;
        
        switch rnd
            case '100'
                LAT(3) = round(LAT(3));
                LONG(3) = round(LONG(3));
            case '10'
                LAT(3) = round(LAT(3)*10)/10;
                LONG(3) = round(LONG(3)*10)/10;
            case '1'
                LAT(3) = round(LAT(3)*100)/100;
                LONG(3) = round(LONG(3)*100)/100;
            otherwise
                error('Wrong flag')
        end
        
    otherwise
        error('Wrong flag')
        
end

end

