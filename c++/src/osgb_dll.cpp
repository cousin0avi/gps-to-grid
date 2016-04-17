#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "osgb_dll.h"
#include "core_dll.h"


void os_ellipsoid (double *os)
{
	os[1] = 6377563.396;
	os[2] = 6356256.909;
	os[0] = 1.0 - (os[2]*os[2])/(os[1]*os[1]);
}

void get_os_tmp(double *os_tmp)
{
	const double pi=3.1415926536;
	
	os_tmp[0] = 0.9996012717; //F_0
	os_tmp[1] = 49*pi/180.0;  // latitude_0
	os_tmp[2] = -2*pi/180.0; // longitude_0
	os_tmp[3] = 400000.0; // Easting_0
	os_tmp[4] = -100000.0; // Northing_0
}

void get_gps_os_rotate(double *ellip_trans_params)
{
	ellip_trans_params[0] = -446.448; //tx
    ellip_trans_params[1] =  125.157; //ty
    ellip_trans_params[2] = -542.060; //tz 
    
    ellip_trans_params[3] = -0.1502 * 4.8481368e-6; //rx
    ellip_trans_params[4] = -0.2470 * 4.8481368e-6; //ry
    ellip_trans_params[5] = -0.8421 * 4.8481368e-6; //rz
    
    ellip_trans_params[6] =  20.4894 * 1.0e-6; //scale factor
}

 std::vector<std::string> get_os_letter_code(void)
{
	std::vector<std::string> os_letter_code = {
		"SV","SW","SX","SY","SZ","TV","TW",
		"SQ","SR","SS","ST","SU","TQ","TR",
		"SL","SM","SN","SO","SP","TL","TM",
		"SF","SG","SH","SJ","SK","TF","TG",
		"SA","SB","SC","SD","SE","TA","TB",
		"NV","NW","NX","NY","NZ","OV","OW",
		"NQ","NR","NS","NT","NU","OQ","OR",
		"NL","NM","NN","NO","NP","OL","OM",
		"NF","NG","NH","NJ","NK","OF","OG",
		"NA","NB","NC","ND","NE","OA","OB",
		"HV","HW","HX","HY","HZ","JV","JW",
		"HQ","HR","HS","HT","HU","JQ","JR",	
		"HL","HM","HN","HO","HP","JL","JM"};
	
	return os_letter_code;
}

int test_os_letter_code(std::string test_code)
{
	std::vector<std::string> let_codes = get_os_letter_code();
	
	if(std::find(let_codes.begin(), let_codes.end(), test_code) != let_codes.end()) {
		return 0; /* v does contain x */
	} else {
		return 1; /* v does not contain x */
	}

}

void get_os_gps_rotate(double *ellip_trans_params)
{
	get_gps_os_rotate(ellip_trans_params);
	
	ellip_trans_params[0] = -ellip_trans_params[0];
    ellip_trans_params[1] = -ellip_trans_params[1];
    ellip_trans_params[2] = -ellip_trans_params[2];
    
    ellip_trans_params[3] = -ellip_trans_params[3];
    ellip_trans_params[4] = -ellip_trans_params[4];
    ellip_trans_params[5] = -ellip_trans_params[5];
    
    ellip_trans_params[6] = -ellip_trans_params[6];
}

std::string convert_os_number_grid_letter(double *OS,double *X)
{
	std::vector<std::string> os_letter_code = get_os_letter_code();
	
	double idx_e = floor(X[0]/100000.0);
	double idx_n = floor(X[1]/100000.0);
	int idx = int(idx_e) + 7*int(idx_n);
	
	std::string let_code = std::string(os_letter_code[idx]); 
	
	OS[0] = X[0] - idx_e*100000.0 ;
	OS[1] = X[1] - idx_n*100000.0 ;
	
	return let_code;
}

void convert_os_grid_letter_number(double *OS,std::string let_code,int prec)
{
	std::vector<std::string> os_codes = get_os_letter_code();	
	std::vector<std::string>::iterator it;
	int pos = std::find(os_codes.begin(),os_codes.end(),let_code)  - os_codes.begin();

	div_t divresult = div(pos,7);
	int e_idx = divresult.rem;
	int n_idx = divresult.quot;
	
	switch(prec){
	case 3:
		OS[0] = OS[0]*100.0;
		OS[1] = OS[1]*100.0;
		break;
	case 4:
		OS[0] = OS[0]*10.0;
		OS[1] = OS[1]*10.0;
		break;
	case 5:
		break;
	default:
		std::cout << "Wrong precision flag" << std::endl;
	}
	
	OS[0] = OS[0] + 100000.0*double(e_idx);
	OS[1] = OS[1] + 100000.0*double(n_idx);
}

std::string gps2os(double phi,double lambda,double h, int prec)
{
	const double pi = 3.1415926536;
	double X[3];
	double nu;
	
	//convert to radians
	phi = phi*pi/180.0;
	lambda = lambda*pi/180.0;
	
	// Get ellipsoid params
	double gps_ellip[3];
	double os_ellip[3];
	gps_ellipsoid(gps_ellip);
	os_ellipsoid(os_ellip);
	
	// Get TMP params
	double os_tmp[5];
	get_os_tmp(os_tmp);
	
	//Get gpr to os ellipsoid params 
	double ellip_trans_params[7];
	get_gps_os_rotate(ellip_trans_params);
	
	// Convert lat-long to cartesian
	latlong_cart(X,gps_ellip,phi, lambda, h );
	
	// Transform to Airy 1830 ellipsoid
	rotate_ellipsoid(X,ellip_trans_params);
	
	// Convert cartesian into lat-long
	cart_latlong(X,os_ellip);
	
	// Convert lat-long to eastings and northings
	latlong_eastings(X,os_ellip,os_tmp,prec);
	
	// Convert number grid to letter grid
	std::string let_code(2,'0');
	double OS[2];
	let_code = convert_os_number_grid_letter(OS,X);
	
	//Convert grid to str for printing
	std::string east(prec,'Z');
	std::string north(prec,'Z'); 
	
	east = convert_grid_str(east,OS[0],prec);
	north = convert_grid_str(north,OS[1],prec);
	
	std::string sep_char = "  ";
	
	std::string out = let_code + sep_char + east + sep_char + north;

	return out;
}

std::string os2gps(std::string let_code,double east,double north, double h,char *d_m_s , int prec) {
	const double pi = 3.1415926536;
	
	double OS[2],X[3];
	OS[0] = east;
	OS[1] = north;
	
	// Get ellipsoid params
	double gps_ellip[3];
	double os_ellip[3];
	gps_ellipsoid(gps_ellip);
	os_ellipsoid(os_ellip);
	
	// Get TMP params
	double os_tmp[5];
	get_os_tmp(os_tmp);
	
	//Get os to gpss ellipsoid params 
	double ellip_trans_params[7];
	get_os_gps_rotate(ellip_trans_params);
	
	//Take OS letter code and convert to easting-northing
	convert_os_grid_letter_number(OS,let_code,prec);
	
	//Convert to lat-long
	eastings_latlong(OS,os_ellip,os_tmp);
	
	// Convert lat-long to cartesian
	latlong_cart(X,os_ellip,OS[0], OS[1], h );
	
	// Transform to GPS ellipsoid
	rotate_ellipsoid(X,ellip_trans_params);
	
	// Convert cartesian into lat-long
	cart_latlong(X,gps_ellip);
	
	// Convert to degrees
	X[0] = X[0]*180.0/pi;
	X[1] = X[1]*180.0/pi;
	
	// Convert array to string
	std::string out;
	out = convert_lat_long_str(X,d_m_s,prec);
	
	return out;
}