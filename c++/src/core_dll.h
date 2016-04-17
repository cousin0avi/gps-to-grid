#ifndef CORE_DLL_H
#define CORE_DLL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILDING_CORE_DLL
#define CORE_DLL __declspec(dllexport)
#else
#define CORE_DLL __declspec(dllimport)
#endif

void gps_ellipsoid (double *gps);
std::string to_string_with_precision(const double a, const int prec);
std::string convert_grid_str(std::string east,double grid,int prec);
std::string convert_lat_long_str(double *X,char *d_m_s,int prec);
void latlong_cart (double *CC,double *ellips,double phi, double lambda, double h );
void rotate_ellipsoid(double *X,double *ellip_trans_params);
void cart_latlong(double *X,double *ellips);
void latlong_eastings(double *X,double *ellips,double *tmp,int prec);
void eastings_latlong(double *X,double *ellips,double *tmp);

#ifdef __cplusplus
}
#endif

#endif  // CORE_DLL_H