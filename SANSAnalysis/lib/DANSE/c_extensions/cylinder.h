#if !defined(cylinder_h)
#define cylinder_h

/** Structure definition for cylinder parameters 
 * [PYTHONCLASS] = CylinderModel
 * */
typedef struct {
    /// Scale factor 
    //  [DEFAULT]=scale=1.0
    double scale;
    /// Radius of the cylinder [A]
    //  [DEFAULT]=radius=20.0 A 
    double radius;
    /// Length of the cylinder [A]
    //  [DEFAULT]=length=400.0 A
    double length;
    /// Contrast [A-2]
    //  [DEFAULT]=contrast=3.0e-6 A-2
    double contrast;
	/// Incoherent Background (cm-1) 0.000
	//  [DEFAULT]=background=0 cm-1
	double background;    
    /// Orientation of the cylinder axis w/respect incoming beam [rad]
    //  [DEFAULT]=cyl_theta=1.0 rad
    double cyl_theta;
    /// Orientation of the cylinder in the plane of the detector [rad]
    //  [DEFAULT]=cyl_phi=1.0 rad
    double cyl_phi;    
} CylinderParameters;



/// 1D scattering function
double cylinder_analytical_1D(CylinderParameters *pars, double q);

/// 2D scattering function
double cylinder_analytical_2D(CylinderParameters *pars, double q, double phi);
double cylinder_analytical_2DXY(CylinderParameters *pars, double qx, double qy);
double cylinder_analytical_2D_scaled(CylinderParameters *pars, double q, double q_x, double q_y);

#endif
