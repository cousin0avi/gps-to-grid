#ifndef OSGB_DLL_H
#define OSGB_DLL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILDING_OSGB_DLL
#define OSGB_DLL __declspec(dllexport)
#else
#define OSGB_DLL __declspec(dllimport)
#endif

void os_ellipsoid (double *os);
void get_gps_os_rotate(double *ellip_trans_params);
void get_os_gps_rotate(double *ellip_trans_params);
std::vector<std::string> get_os_letter_code(void);
int test_os_letter_code(std::string test_code);
void convert_os_grid_letter_number(double *OS,std::string let_code,int prec);
void get_os_tmp(double *os_tmp);
std::string convert_os_number_grid_letter(double *OS,double *X);

std::string gps2os(double phi,double lambda,double h, int prec);
std::string os2gps(std::string let_code,double east,double north, double h, char *d_m_s, int prec);

#ifdef __cplusplus
}
#endif

#endif  // OSGB_DLL_H