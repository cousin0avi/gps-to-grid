#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "core_dll.h"

void gps_ellipsoid (double *gps)
{
	gps[1] = 6378137.0000;
	gps[2] = 6356752.3141;
	gps[0] = 1 - (gps[2]*gps[2])/(gps[1]*gps[1]);
}

std::string to_string_with_precision(const double a, const int prec)
{
	std::ostringstream out;
	out << std::fixed << std::setprecision(prec) << a;
	return out.str();
}

std::string convert_grid_str(std::string str,double grid,int prec)
{
	switch (prec)
	{
		case 5:
			break;
		case 4:
			grid = grid/10.0;
			break;
		case 3:
			grid = grid/100.0;
			break;
		default:
			return str;
	}
	
	int n_digit = int(floor(log10(abs(grid)+1.0)) + 1.0);
	
	std::string tmp_str(prec,'0');
	int a =5;
	double d;
	
	for(int ii=(prec-1);ii>(prec-n_digit-1);ii=ii-1)
	{
		d = fmod(grid,10);
		tmp_str[ii] = '0' + int(d);
		grid = (grid-d)/10.0;
	}
	
	str = tmp_str;
	
	return str;
}

std::string convert_lat_long_str(double *X,char *d_m_s,int prec)
{
	// Get N,S and E,W
	std::string N_S(1,'N');
	std::string E_W(1,'E');
	
	if (X[0]<0.0) {
		N_S = "S";
		X[0] = fabs(X[0]);
	}
	if (X[1]<0.0) {
		E_W = "W";
		X[1] = fabs(X[1]);
	}

	std::string out,lat_deg,lon_deg;
	std::string sep_char = "  ";
	int out_prec;
	
	if (*d_m_s=='d'){
		switch (prec){
            case 3:
				out_prec = 3;
				break;
            case 4:
				out_prec = 4;
				break;
            case 5:
                out_prec = 5;
				break;
            default:
                std::cout << "Error: Invalid precision flag" << std::endl;
				return out;
		}
		
		double multiplier_prec = pow(10.0,double(out_prec));
		X[0] = round(X[0]*multiplier_prec)/multiplier_prec;
        X[1] = round(X[1]*multiplier_prec)/multiplier_prec;
	
		lat_deg = to_string_with_precision(X[0],out_prec);
		lon_deg = to_string_with_precision(X[1],out_prec);
		
		out = N_S + sep_char + lat_deg + sep_char + E_W + sep_char + lon_deg;
		return out;
	}
	
	double lat = floor(X[0]);
	double lon = floor(X[1]);
	
	lat_deg = std::to_string(int(lat));
	lon_deg = std::to_string(int(lon));
	
	X[0] = (X[0] - lat)*60.0;
	X[1] = (X[1] - lon)*60.0;
	
	std::string lat_min,lon_min;
	
	if (*d_m_s=='m'){
		switch (prec){
            case 3:
                out_prec = 2;
				break;
            case 4:
                out_prec = 3;
				break;
            case 5:
                out_prec = 4;
				break;
            default:
                std::cout << "Error: Invalid precision flag" << std::endl;
				return out;
		}
		
		double multiplier_prec = pow(10.0,double(out_prec));
		X[0] = round(X[0]*multiplier_prec)/multiplier_prec;
        X[1] = round(X[1]*multiplier_prec)/multiplier_prec;
		
		lat_min = to_string_with_precision(X[0],out_prec);
		lon_min = to_string_with_precision(X[1],out_prec);
		
		out = N_S + sep_char + lat_deg + sep_char + lat_min + sep_char + 
			  E_W + sep_char + lon_deg + sep_char + lon_min;
		return out;
	}
	
	lat = floor(X[0]);
	lon = floor(X[1]);
	
	lat_deg = std::to_string(int(lat));
	lon_deg = std::to_string(int(lon));
	
	X[0] = (X[0] - lat)*60.0;
	X[1] = (X[1] - lon)*60.0;
	
	std::string lat_sec,lon_sec;
	
	if (*d_m_s=='s'){
		switch (prec){
            case 3:
                out_prec = 0;
				break;
            case 4:
                out_prec = 1;
				break;
            case 5:
                out_prec = 2;
				break;
            default:
                std::cout << "Error: Invalid precision flag" << std::endl;
				return out;
		}
		
		double multiplier_prec = pow(10.0,double(out_prec));
		X[0] = round(X[0]*multiplier_prec)/multiplier_prec;
        X[1] = round(X[1]*multiplier_prec)/multiplier_prec;
		
		lat_sec = to_string_with_precision(X[0],out_prec);
		lon_sec = to_string_with_precision(X[1],out_prec);
		
		out = N_S + sep_char + lat_deg + sep_char + lat_min + sep_char + lat_sec + sep_char +
			  E_W + sep_char + lon_deg + sep_char + lon_min + sep_char + lon_sec;
		return out;
	}
	
	std::cout << "Error: Wrong DMS flag" << std::endl;
	std::string bad="Error";
	return bad;
}

void latlong_cart (double *CC,double *ellips,double phi, double lambda, double h )
{
	double nu = ellips[1]/( sqrt(1-ellips[0]*sin(phi)*sin(phi)) );
	
	CC[0] = (nu + h)*cos(phi)*cos(lambda);
    CC[1] = (nu + h)*cos(phi)*sin(lambda);
    CC[2] = ((1.0-ellips[0])*nu + h)*sin(phi);
}

void rotate_ellipsoid(double *X,double *ellip_trans_params)
{
	double x0 = X[0];
	double x1 = X[1];
	double x2 = X[2];
	
	X[0] = ellip_trans_params[0] + (1.0+ellip_trans_params[6])*x0 - ellip_trans_params[5]*x1 + ellip_trans_params[4]*x2;
	X[1] = ellip_trans_params[1] + ellip_trans_params[5]*x0 + (1.0+ellip_trans_params[6])*x1 - ellip_trans_params[3]*x2;
	X[2] = ellip_trans_params[2] - ellip_trans_params[4]*x0 + ellip_trans_params[3]*x1 + (1.0+ellip_trans_params[6])*x2;
}

void cart_latlong(double *X,double *ellips)
{
	double p = sqrt(X[0]*X[0] + X[1]*X[1]);

	X[1] = atan(X[1]/X[0]);

	double phi = 0.0;
	double phi1 = 0.0;
	double check = 1.0;
	double nu = 1.0;

	phi = atan( X[2]/( p*(1.0-ellips[0]) ) );

	while (check > 1.0e-9)
	{
		nu = ellips[1]/sqrt( 1.0-ellips[0]*sin(phi)*sin(phi) );
		phi1 = atan( (X[2] + ellips[0]*nu*sin(phi))/p );
		check = std::abs(phi1-phi)/phi;
		phi = phi1;
	}
	
	X[0] = phi;
	X[2] = p/cos(X[0]) - nu;
}

void latlong_eastings(double *X,double *ellips,double *tmp,int prec)
{
	double ome2sp = 1.0-ellips[0]*sin(X[0])*sin(X[0]);

	double d_long = X[1] - tmp[2];
	double d_long2 = d_long*d_long;
	double d_long4 = d_long2*d_long2;

	double d_phi = X[0] - tmp[1];
	double s_phi = X[0] + tmp[1];

	double n = (ellips[1]-ellips[2])/(ellips[1]+ellips[2]);
	double nu = ellips[1]*tmp[0]/sqrt(ome2sp);
	double rho = ellips[1]*tmp[0]*(1-ellips[0])*pow(ome2sp,-1.5);
	double eta2 = nu/rho - 1.0;

	double M = ellips[2]*tmp[0]*( (1.0+n+1.25*n*n+1.25*n*n*n)*d_phi - 
		(3.0*n+3.0*n*n +2.625*n*n*n)*sin(d_phi)*cos(s_phi) + 
		(1.875*n*n + 1.875*n*n*n)*sin(2.0*d_phi)*cos(2.0*s_phi) - 
		35.0/24.0*n*n*n*sin(3.0*d_phi)*cos(3.0*s_phi) );

	double cos_lat = cos(X[0]);
	double sin_lat = sin(X[0]);
	double tan_lat_2 = tan(X[0])*tan(X[0]);
	double cos_lat_3 = cos_lat*cos_lat*cos_lat;
	double cos_lat_5 = cos_lat_3*cos_lat*cos_lat;

	double i1 = M + tmp[4];
	double ii = nu/2.0*sin_lat*cos_lat;
	double iii = nu/24.0*sin_lat*cos_lat_3*(5-tan_lat_2+9*eta2);
	double iiia = nu/720.0*sin_lat*cos_lat_5*(61.0 - 58.0*tan_lat_2+tan_lat_2*tan_lat_2 );
	double iv = nu*cos_lat;
	double v = nu/6.0*cos_lat_3*(nu/rho - tan_lat_2);
	double vi = nu/120.0*cos_lat_5*( 5.0-18.0*tan_lat_2+tan_lat_2*tan_lat_2+14.0*eta2-58.0*eta2*tan_lat_2 );

	X[1] = i1 + (ii + iii*d_long2 + iiia*d_long4)*d_long2;
	X[0] = tmp[3] + (iv + v*d_long2 + vi*d_long4)*d_long;
	
	switch (prec) {
		case 3 :
			X[0] = round(X[0]/100.0)*100.0;
			X[1] = round(X[1]/100.0)*100.0;
			break;
		case 4 :
			X[0] = round(X[0]/10.0)*10.0;
			X[1] = round(X[1]/10.0)*10.0;
			break;
		case 5 :
			X[0] = round(X[0]);
			X[1] = round(X[1]);
			break;
		case 0 :
			break;
		default :
				std::cout << "Error: Invalid precision flag" << std::endl;
	}
	
}

void eastings_latlong(double *X,double *ellips,double *tmp)
{
	double n = (ellips[1]-ellips[2])/(ellips[1]+ellips[2]);

	// Iterate to find latitude' 
	double phi_p = (X[1] - tmp[4])/(ellips[1]*tmp[0]) + tmp[1];
	double diff = 1.0;
	double d_phi,s_phi,M,phi_p1;

	while (diff>1e-9) {
		d_phi = phi_p-tmp[1];
		s_phi = phi_p+tmp[1];
    
		M = ellips[2]*tmp[0]*(
			(1.0+n+1.25*n*n+1.25*n*n*n)*(d_phi) - 
			(3.0*n+3.0*n*n + 2.625*n*n*n)*sin(d_phi)*cos(s_phi) + 
			(1.875*n*n + 1.875*n*n*n)*sin(2.0*d_phi)*cos(2.0*s_phi) - 
			35.0/24.0*n*n*n*sin(3.0*d_phi)*cos(3.0*s_phi) );
		
			phi_p1 = (X[1] - tmp[4] - M)/(ellips[1]*tmp[0]) + phi_p;
    
		diff = abs(X[1] - tmp[4] - M)/X[1];
		phi_p = phi_p1;
	}

	double ome2sp = 1.0-ellips[0]*(sin(phi_p)*sin(phi_p));
	double nu = ellips[1]*tmp[0]/sqrt(ome2sp);
	double rho = ellips[1]*tmp[0]*(1.0-ellips[0])*pow(ome2sp,-1.5);
	double eta2 = nu/rho - 1.0;

	double nu3 = nu * nu *nu;
	double nu5 = nu3*nu*nu;
	double nu7 = nu5*nu*nu;

	double tan_p = tan(phi_p);
	double tan2_p = tan_p*tan_p;
	double tan4_p = tan2_p*tan2_p;

	double sec_p = 1.0/cos(phi_p);

	double vii = tan_p/(2.0*rho*nu);
	double viii = tan_p/(24.0*rho*nu3)*( 5.0+3.0*tan2_p + eta2 - 9*eta2*tan2_p);
	double ix = tan_p/(720.0*rho*nu5)*( 61.0 +90.0*tan2_p+45.0*tan4_p );
	double x = sec_p/nu;
	double xi = sec_p/(6.0*nu3)*( nu/rho + 2.0*tan2_p );
	double xii = sec_p/(120.0*nu5)*( 5.0+28.0*tan2_p+24.0*tan4_p );
	double xiia = sec_p/(5040.0*nu7)*( 61.0+662.0*tan2_p+1320.0*tan4_p+720.0*tan4_p*tan2_p );

	double E_diff = (X[0]-tmp[3]);
	double E_diff_2 = E_diff*E_diff;
	double E_diff_4 = E_diff_2*E_diff_2;

	X[0] = phi_p  - (vii + viii*E_diff_2 - ix*E_diff_4)*E_diff_2;
	X[1] = tmp[2] + (x - xi*E_diff_2 + xii*E_diff_4 - xiia*E_diff_2*E_diff_4)*E_diff;
}