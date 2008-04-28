/*
 * test2D.c
 * Return 2D I for cylinders
 *
 * A Jackson, May 2007
 */

#include "../lib/libSANSAnalysis.h"
#include <math.h>
#include <stdio.h>

int main(){
	double qx[128],qy[128],i[128][128];
	// Model params:
	// params[0]: scale factor
	// params[1]: radius of the cylinder [A]
	// params[2]: length of the cylinder [A]
	// params[3]: contrast [A-2] 
 	// params[4]: background [cm-1]
	// params[5]: angle theta of the cylinder axis and beam [rad]
	// params[6]: angle phi of the cylinder axis and x-axis (horizontal)
	// params[7]: standard deviation of theta
 	// params[8]: standard deviation of phi
 	// params[9]: standard deviation of radius		
	double params[] = {1,50,500,3e-6,0.01,0,0,0,0,0};
	int ii,jj;

	double q,phi;
	
	for (ii = 0; ii < 128; ii++){
		qx[ii] = -0.50 + (0.5)*2*ii/128;
//		fprintf(stderr, "Qx = %g\n", qx[ii]);
		for (jj = 0; jj < 128; jj++){
			qy[jj] = -0.50 + (0.5)*2*jj/128;
			//Call the form factor calculation
			q = hypot(qx[ii],qy[jj]);
			phi = atan2(qy[jj],qx[ii]);
//			fprintf(stderr, "Qx = %g; Qy = %g ==> Q = %g; Phi = %g", qx[ii], qy[jj], q, phi);
			i[ii][jj] = dist_cylinder_2D(params,qx[ii],qy[jj]);
//			fprintf(stderr, " ==> I(Q) = %g\n", i[ii][jj]);
		}
	}

	for (jj = 0; jj < 128; jj++){
		for (ii = 0; ii < 128; ii++){
			printf("%g ",i[ii][jj]);
		}
		printf("\n");
	}

	return 0;
}
