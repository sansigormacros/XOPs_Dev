/*
 *  Func2D.c
 *  SANSAnalysis
 *
 * Steve Kline Jan 2008
 * these are the XOP calls to DANSE 2D functions
 * from the library supplied by M. Doucet
 *
 */


#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "SANSAnalysis.h"				// structures, two-byte aligned
#include "libSANSAnalysis.h"			// functions from the libSANS	
#include "danse.h"						// functions from the DANSE part of libSANS
#include <math.h>
#include "Func2D.h"						// declarations for the 2D functions in this file

int
Cylinder_2D(FitParams2DPtr p)
{
	double *dp;
	
	float *fp;				// Pointer to single precision wave data.
	double qx;
	double qy;
	double q, phi;
	double pars[11];
//	int i;
//	char buf[256];
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
    
	qx = p->qx;
	qy = p->qy;
	
//	sprintf(buf, "Qx = %g, Qy = %g\r",qx, qy);
//	XOPNotice(buf);

	q = hypot(qx,qy);
	phi = atan2(qy,qx);
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= (float*)WaveData(p->waveHandle);
            SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07            
		case NT_FP64:
			dp= (double*)WaveData(p->waveHandle);
			
//			for(i=0; i<11; i++) {
//				pars[i] = dp[i];
//			}
			pars[0] = dp[0];
			pars[1] = dp[1];
			pars[2] = dp[2];
			pars[3] = dp[3] - dp[4];
			pars[4] = dp[5];
			pars[5] = dp[6];
			pars[6] = dp[7];
			pars[7] = dp[8];
			pars[8] = dp[9];
			pars[9] = dp[10];
			pars[10] = dp[11];

			p->result = disperse_cylinder_analytical_2D( pars, q, phi ); 
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

int
Cylinder_2D_Weight2D(FitParams2DWeightPtr p)
{
	double *dp;
	
	float *fp;				// Pointer to single precision wave data.
	double qx;
	double qy;
	double q, phi;
	double *par_values;
	double *weight_values;
	double pars[13];
	int i, i_theta;
	double sum;
	int n_slices;
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
    
	qx = p->qx;
	qy = p->qy;
	
	q = hypot(qx,qy);
	phi = atan2(qy,qx);
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= (float*)WaveData(p->waveHandle);
            SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07            
		case NT_FP64:
			dp= (double*)WaveData(p->waveHandle);
			par_values = (double*)WaveData(p->par_values);
			weight_values = (double*)WaveData(p->weight_values);
			
			for(i=0; i<13; i++) {
				pars[i] = dp[i];
			}

			sum = 0.0;
			n_slices = (int)floor(dp[13]);

			//XOPOKAlert("test","This is a test");

			if(n_slices == 0) {
				p->result =weight_dispersion( &disperse_cylinder_analytical_2D,
							par_values, weight_values, 
							(int)floor(pars[11]), (int)floor(pars[12]),
							pars, q, phi ); 		
			} else {
				for(i_theta=0; i_theta<n_slices; i_theta++) {
					SpinProcess();
					// average over theta
					
					// For the cylinder model, theta_cyl=90 degrees
					// will produce a NAN at phi_cyl=0 and 45 degrees
					pars[5] = acos(-1.0)/n_slices * i_theta;
					if( fabs(i_theta / n_slices) - 0.5 < 0.000001 ) {
						//continue;
						pars[5] += 0.00001;
					}
					
					// Multiply by sin(theta) because we are integrating in
					// spherical coordinates
					sum += sin(pars[5])* weight_dispersion( &disperse_cylinder_analytical_2D,
								par_values, weight_values, 
								(int)floor(pars[11]), (int)floor(pars[12]),
								pars, q, phi ); 
				}
				
				p->result = sum/n_slices;
			}
			
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

int
CoreShellCylinder_2D(FitParams2DPtr p)
{
	double *dp;
	
	float *fp;				// Pointer to single precision wave data.
	double qx;
	double qy;
	double q, phi;
	double pars[15];
	int i;
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
    
	qx = p->qx;
	qy = p->qy;
	
	q = hypot(qx,qy);
	phi = atan2(qy,qx);
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= (float*)WaveData(p->waveHandle);
            SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07            
		case NT_FP64:
			dp= (double*)WaveData(p->waveHandle);
			
			for(i=0; i<15; i++) {
				pars[i] = dp[i];
			}

			p->result = disperse_core_shell_cylinder_analytical_2D( pars, q, phi ); 
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

int
CoreShellCylinder_2D_Weight2D(FitParams2DWeightPtr p)
{
	double *dp;
	
	float *fp;				// Pointer to single precision wave data.
	double qx;
	double qy;
	double q, phi;
	double *par_values;
	double *weight_values;
	double pars[17];
	int i, i_theta;
	double sum;
	int n_slices;
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
    
	qx = p->qx;
	qy = p->qy;
	
	q = hypot(qx,qy);
	phi = atan2(qy,qx);
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= (float*)WaveData(p->waveHandle);
            SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07            
		case NT_FP64:
			dp= (double*)WaveData(p->waveHandle);
			par_values = (double*)WaveData(p->par_values);
			weight_values = (double*)WaveData(p->weight_values);
			
			for(i=0; i<17; i++) {
				pars[i] = dp[i];
			}

			sum = 0.0;
			n_slices = (int)floor(dp[17]);

			if(n_slices == 0) {
				p->result =weight_dispersion( &disperse_core_shell_cylinder_analytical_2D,
							par_values, weight_values, 
							(int)floor(pars[15]), (int)floor(pars[16]),
							pars, q, phi ); 		
			} else {
				for(i_theta=0; i_theta<n_slices; i_theta++) {
					SpinProcess();
					// average over theta
					
					// For the cylinder model, theta_cyl=90 degrees
					// will produce a NAN at phi_cyl=0 and 45 degrees
					// TODO: integrate from 0 to pi/2 instead of 0 to pi
					pars[8] = acos(-1.0)/n_slices * i_theta;
					if( fabs(i_theta / n_slices) - 0.5 < 0.000001 ) {
						//continue;
						pars[8] += 0.00001;
					}
					
					// Multiply by sin(theta) because we are integrating in
					// spherical coordinates
					sum += sin(pars[8])* weight_dispersion( &disperse_core_shell_cylinder_analytical_2D,
								par_values, weight_values, 
								(int)floor(pars[15]), (int)floor(pars[16]),
								pars, q, phi ); 
				}
				
				p->result = sum/n_slices;
			}
			
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

int
Ellipsoid_2D(FitParams2DPtr p)
{
	double *dp;
	
	float *fp;				// Pointer to single precision wave data.
	double qx;
	double qy;
	double q, phi;
	double pars[12];
//	int i;
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
    
	qx = p->qx;
	qy = p->qy;
	
	q = hypot(qx,qy);
	phi = atan2(qy,qx);
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= (float*)WaveData(p->waveHandle);
            SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07            
		case NT_FP64:
			dp= (double*)WaveData(p->waveHandle);
			
//			for(i=0; i<12; i++) {
//				pars[i] = dp[i];
//			}
			pars[0] = dp[0];
			pars[1] = dp[1];
			pars[2] = dp[2];
			pars[3] = dp[3] - dp[4];
			pars[4] = dp[5];
			pars[5] = dp[6];
			pars[6] = dp[7];
			pars[7] = dp[8];
			pars[8] = dp[9];
			pars[9] = dp[10];
			pars[10] = dp[11];
			pars[11] = dp[12];

			//p->result = 1.0;
			p->result = disperse_ellipsoid_analytical_2D( pars, q, phi ); 
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

int
Ellipsoid_2D_Weight2D(FitParams2DWeightPtr p)
{
	double *dp;
	
	float *fp;				// Pointer to single precision wave data.
	double qx;
	double qy;
	double q, phi;
	double *par_values;
	double *weight_values;
	double pars[14];
	int i, i_theta;
	double sum;
	int n_slices;
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
    
	qx = p->qx;
	qy = p->qy;
	
	q = hypot(qx,qy);
	phi = atan2(qy,qx);
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= (float*)WaveData(p->waveHandle);
            SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07            
		case NT_FP64:
			dp= (double*)WaveData(p->waveHandle);
			par_values = (double*)WaveData(p->par_values);
			weight_values = (double*)WaveData(p->weight_values);
			
			for(i=0; i<14; i++) {
				pars[i] = dp[i];
			}

			sum = 0.0;
			n_slices = (int)floor(dp[14]);

			if(n_slices == 0) {
				p->result =weight_dispersion( &disperse_ellipsoid_analytical_2D,
							par_values, weight_values, 
							(int)floor(pars[12]), (int)floor(pars[13]),
							pars, q, phi ); 		
			} else {
				for(i_theta=0; i_theta<n_slices; i_theta++) {
					SpinProcess();
					// average over theta
					
					// For the cylinder model, theta_cyl=90 degrees
					// will produce a NAN at phi_cyl=0 and 45 degrees
					pars[5] = acos(-1.0)/n_slices * i_theta;
					if( fabs(i_theta / n_slices) - 0.5 < 0.000001 ) {
						//continue;
						pars[5] += 0.00001;
					}
					
					// Multiply by sin(theta) because we are integrating in
					// spherical coordinates
					sum += sin(pars[5])* weight_dispersion( &disperse_ellipsoid_analytical_2D,
								par_values, weight_values, 
								(int)floor(pars[12]), (int)floor(pars[13]),
								pars, q, phi ); 
				}
				
				p->result = sum/n_slices;
			}
			
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}


int
EllipticalCylinder_2D(FitParams2DPtr p)
{
	double *dp;
	
	float *fp;				// Pointer to single precision wave data.
	double qx;
	double qy;
	double q, phi;
	double pars[14];
//	int i;
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
    
	qx = p->qx;
	qy = p->qy;
	
	q = hypot(qx,qy);
	phi = atan2(qy,qx);
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= (float*)WaveData(p->waveHandle);
            SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07            
		case NT_FP64:
			dp= (double*)WaveData(p->waveHandle);
			
//			for(i=0; i<14; i++) {
//				pars[i] = dp[i];
//			}
			pars[0] = dp[0];
			pars[1] = dp[1];
			pars[2] = dp[2];
			pars[3] = dp[3];
			pars[4] = dp[4] - dp[5];
			pars[5] = dp[6];
			pars[6] = dp[7];
			pars[7] = dp[8];
			pars[8] = dp[9];
			pars[9] = dp[10];
			pars[10] = dp[11];
			pars[11] = dp[12];
			pars[12] = dp[13];
			pars[13] = dp[14];

			
			p->result = disperse_elliptical_cylinder_analytical_2D( pars, q, phi ); 
			 
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

int
EllipticalCylinder_2D_Weight2D(FitParams2DWeightPtr p)
{
	double *dp;
	
	float *fp;				// Pointer to single precision wave data.
	double qx;
	double qy;
	double q, phi;
	double *par_values;
	double *weight_values;
	double pars[16];
	int i, i_theta;
	double sum;
	int n_slices;
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
    
	qx = p->qx;
	qy = p->qy;
	
	q = hypot(qx,qy);
	phi = atan2(qy,qx);
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= (float*)WaveData(p->waveHandle);
            SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07            
		case NT_FP64:
			dp= (double*)WaveData(p->waveHandle);
			par_values = (double*)WaveData(p->par_values);
			weight_values = (double*)WaveData(p->weight_values);
			
			for(i=0; i<16; i++) {
				pars[i] = dp[i];
			}

			sum = 0.0;
			n_slices = (int)floor(dp[16]);

			if(n_slices == 0) {
				p->result =weight_dispersion( &disperse_elliptical_cylinder_analytical_2D,
							par_values, weight_values, 
							(int)floor(pars[14]), (int)floor(pars[15]),
							pars, q, phi ); 		
			} else {
				for(i_theta=0; i_theta<n_slices; i_theta++) {
					SpinProcess();
					// average over theta
					
					// For the cylinder model, theta_cyl=90 degrees
					// will produce a NAN at phi_cyl=0 and 45 degrees
					// TODO: integrate from 0 to pi/2 instead of 0 to pi
					
					pars[6] = acos(-1.0)/n_slices * i_theta;
					
					 if( fabs(i_theta / n_slices) - 0.5 < 0.000001 ) {
						//continue;
						pars[6] += 0.00001;
					}
					
					// Multiply by sin(theta) because we are integrating in
					// spherical coordinates
					sum += sin(pars[6])* weight_dispersion( &disperse_elliptical_cylinder_analytical_2D,
								par_values, weight_values, 
								(int)floor(pars[14]), (int)floor(pars[15]),
								pars, q, phi ); 
				}
				
				p->result = sum/n_slices;
			}
			
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}

int
Sphere_2D(FitParams2DPtr p)
{
	double *dp;
	
	float *fp;				// Pointer to single precision wave data.
	double qx;
	double qy;
//	double q, phi;
	double pars[5];
	int i;
//	char buf[256];
	
	if (p->waveHandle == NIL) {
		SetNaN64(&p->result);
		return NON_EXISTENT_WAVE;
	}
    
	qx = p->qx;
	qy = p->qy;
	
//	sprintf(buf, "Qx = %g, Qy = %g\r",qx, qy);
//	XOPNotice(buf);
	

		//not needed for a symmetric scattering function like this
//	q = hypot(qx,qy);
//	phi = atan2(qy,qx);
	
	switch(WaveType(p->waveHandle)){			// We can handle single and double precision coefficient waves.
		case NT_FP32:
			fp= (float*)WaveData(p->waveHandle);
            SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE; //not quite true, but good enough for now AJJ 4/23/07            
		case NT_FP64:
			dp= (double*)WaveData(p->waveHandle);
			
			for(i=0; i<5; i++) {
				pars[i] = dp[i];
			}

			p->result = SphereForm(pars, sqrt(qx*qx+qy*qy));		//kind of a trivial example...
			return 0;
		default:								// We can't handle this wave data type.
			SetNaN64(&p->result);
			return REQUIRES_SP_OR_DP_WAVE;
	}
	
	return 0;
}
