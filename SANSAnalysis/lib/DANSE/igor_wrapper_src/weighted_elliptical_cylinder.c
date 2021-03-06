/**
 * Evaluate EllipticalCylinderModel with angular distribution given
 * by user. 
 * 
 * This code was written as part of the DANSE project
 *  http://danse.us/trac/sans/
 *
 * WARNING: THIS FILE WAS GENERATED BY IGORGENERATOR.PY
 *          DO NOT MODIFY THIS FILE, MODIFY elliptical_cylinder.h
 *          AND RE-RUN THE GENERATOR SCRIPT
 *   
 *  @copyright 2007: University of Tennessee, for the DANSE project
 *
 */

#include "c_disperser.h"
#include "danse.h"
#include <math.h>

/**
 * Evaluate model for given angular distributions in theta and phi.
 * 
 * Angles are in radian.
 * 
 * See disp_elliptical_cylinder.c for more information about the model parameters.
 * 
 * @param dp: model parameters
 * @param phi_values: vector of phi_values
 * @param phi_weights: vector of weights for each entry in phi_values
 * @param n_phi: length of phi_values and phi_weights vectors
 * @param theta_values: vector of theta values
 * @param theta_weights: vector of weights for each entry in theta_values
 * @param n_theta: length of theta_Values and theta_weights vectors
 * @param q: q-value to evaluate the model at
 * @param phi_q: angle between the q-vector and the q_x axis
 * @return: scattering intensity
 * 
    // List of default parameters:
    //         pars[0]:   scale           = 1.0 
    //         pars[1]:   r_minor         = 20.0 A
    //         pars[2]:   r_ratio         = 1.5 A
    //         pars[3]:   length          = 400.0 A
    //         pars[4]:   contrast        = 3e-06 A-2
    //         pars[5]:   background      = 0.0 cm-1
    //         pars[6]:   cyl_theta       = 1.57 rad
    //         pars[7]:   cyl_phi         = 0.0 rad
    //         pars[8]:   cyl_psi         = 0.0 rad

    //         pars[9]:   dispersion of r_minor
    //         pars[10]:   dispersion of r_ratio
    //         pars[11]:   dispersion of cyl_theta
    //         pars[12]:   dispersion of cyl_phi
    //         pars[13]:   number of points in dispersion curve
 * 
 * NOTE: DO NOT USE THETA AND PHI PARAMETERS WHEN
 *       USING THIS FUNCTION TO APPLY ANGULAR DISTRIBUTIONS.
 * 
 */
double elliptical_cylinder_Weights(double dp[], double *phi_values, double *phi_weights, int n_phi, 
								double *theta_values, double *theta_weights, int n_theta, 
								double q, double phi_q) {
	// Copy of parameters
	double pars[14];
	// Parameter index for theta
	int theta_index = 6;
	// Parameter index for phi
	int phi_index   = 7;
	int i, i_theta;
	double sum, norm;
	
	// Copy parameters because they will be modified
	for(i=0; i<14; i++) {
		pars[i] = dp[i];
	}

	if (n_theta == 0) {
		return weight_dispersion( &disperse_elliptical_cylinder_analytical_2D,
				phi_values, phi_weights, n_phi, phi_index, pars, q, phi_q );
	} else {
		sum = 0.0;
		norm = 0.0;
		
		for(i_theta=0; i_theta<n_theta; i_theta++) {
			// Assign new theta value
			pars[theta_index] = theta_values[i_theta];
			// Evaluate the function, weight by sin(theta) 
			sum += sin(theta_values[i_theta]) * theta_weights[i_theta] * 
					weight_dispersion( &disperse_elliptical_cylinder_analytical_2D,
					phi_values, phi_weights, n_phi, phi_index, pars, q, phi_q );
			// Keep track of normalization
			norm += theta_weights[i_theta];
		}
		
		// Protect against null weight vector
		if(norm > 0) {
			return sum/norm;
		}
	}
	return 0.0;
}



