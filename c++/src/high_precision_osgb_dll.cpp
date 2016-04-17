#include "high_precision_osgb_dll.h"

void outArray (double s[4][3], const int idx)
{
	for (int ii=0;ii<4;ii++) {
		for (int jj=0;jj<3;jj++) {
			s[ii][jj] = idx + ii + jj;
	};};

}
