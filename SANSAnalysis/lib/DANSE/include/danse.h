/**
 * DANSE function header
 * 
 * WARNING: THIS FILE WAS GENERATED BY HEADERGENERATOR.PY
 *          DO NOT MODIFY THIS FILE
 *
 *  This code was written as part of the DANSE project
 *  http://danse.us/trac/sans/
 *  
 *  @copyright 2007: University of Tennessee, for the DANSE project
 *
 */
#if !defined(function_header_h)
#define function_header_h

double oriented_core_shell_cylinder_2D(double pars[], double q, double phi);
double disperse_core_shell_cylinder_analytical_2D(double dp[], double q, double phi);
double core_shell_cylinder_Weights(double dp[], double *phi_values, double *phi_weights, int n_phi,
    double *theta_values, double *theta_weights, int n_theta, double q, double phi_q);

double oriented_cylinder_2D(double pars[], double q, double phi);
double disperse_cylinder_analytical_2D(double dp[], double q, double phi);
double cylinder_Weights(double dp[], double *phi_values, double *phi_weights, int n_phi,
    double *theta_values, double *theta_weights, int n_theta, double q, double phi_q);

double oriented_ellipsoid_2D(double pars[], double q, double phi);
double disperse_ellipsoid_analytical_2D(double dp[], double q, double phi);
double ellipsoid_Weights(double dp[], double *phi_values, double *phi_weights, int n_phi,
    double *theta_values, double *theta_weights, int n_theta, double q, double phi_q);

double oriented_elliptical_cylinder_2D(double pars[], double q, double phi);
double disperse_elliptical_cylinder_analytical_2D(double dp[], double q, double phi);
double elliptical_cylinder_Weights(double dp[], double *phi_values, double *phi_weights, int n_phi,
    double *theta_values, double *theta_weights, int n_theta, double q, double phi_q);


#endif


