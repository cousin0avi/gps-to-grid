#ifndef HIGH_PRECISION_OSGB_DLL_H
#define HIGH_PRECISION_OSGB_DLL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILDING_HIGH_PRECISION_OSGB_DLL
#define HIGH_PRECISION_OSGB_DLL __declspec(dllexport)
#else
#define HIGH_PRECISION_OSGB_DLL __declspec(dllimport)
#endif

void outArray (double s[4][3], const int idx) ;

#ifdef __cplusplus
}
#endif

#endif  // HIGH_PRECISION_OSGB_DLL_H