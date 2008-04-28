/*	ResolutionSmearing.c

Generalized smearing routines

*/


#include "XOPStandardHeaders.h"			// Include ANSI headers, Mac headers, IgorXOP.h, XOP.h and XOPSupport.h
#include "SANSAnalysis.h"
#include "GaussWeights.h"
#include "ResolutionSmearing.h"
#include "libSANSAnalysis.h"

int
Smear_Model_20_X(GenSmearParamsPtr p)
{
	PassParams pp;
	FunctionInfo fi;
	int badParameterNumber;
	int requiredParameterTypes[2];
	int err;
	double ans;
	//char buf[256];

	int ii;
	double nord,va,vb,summ,yyy,zi,Pi;
	double answer,Resoln,i_shad,i_qbar,i_sigq;
	
	//Get name of function into string here with
	char func[255];
	GetCStringFromHandle(p->funcname, func, sizeof(func));
	
	//Make sure function that we want to call exists
	//GetFunctionInfo(func,&fi);
	if (err = GetFunctionInfo(func,&fi)){
		//	if (err = GetFunctionInfo("Cyl_PolyRadiusX",&fi)){
		XOPNotice("Error at GetFunctionInfo\r");
		return err;
		}
	requiredParameterTypes[1] = NT_FP64;
	requiredParameterTypes[0] = WAVE_TYPE;
	if (err = CheckFunctionForm(&fi, 2, requiredParameterTypes, &badParameterNumber, NT_FP64)){
		XOPNotice("Error at CheckFunctionForm\r");
		return err;
	};


	
	Pi = 4.0*atan(1.0);
	
	i_shad = p->i_shad;
	i_qbar = p->i_qbar;
	i_sigq = p->i_sigq;
	
	//sprintf(buf, "i_shad = %g, i_qbar = %g, i_sigq = %g", i_shad, i_qbar, i_sigq);
	//XOPNotice(buf);
	
	pp.waveHandle = p->waveHandle;
	pp.x = p->x;
	//need interpolation
	
	if (i_sigq >= 0){
		
		nord = 20;
		va = -3*i_sigq + i_qbar;
		if (va < 0){
			va = 0;
		}
		vb = 3*i_sigq + i_qbar;
		
		summ = 0.0;
		ii=0;
		while (ii < nord) {
			zi = (Gauss20Z[ii]*(vb-va) + va + vb)/2.0;
			pp.x = zi;
			Resoln = i_shad/sqrt(2*Pi*i_sigq*i_sigq);
			Resoln *= exp((-1*pow((zi-i_qbar),2))/(2*i_sigq*i_sigq));
			if (err = CallFunction(&fi, (void*)&pp, &ans)){
				XOPNotice("Error at CallFunction in Gaussian Smear\r");
				return err;
			}
			//			CallFunction(&fi, (void*)&pp, &ans);
			yyy = Gauss20Wt[ii]*Resoln*ans;
			summ += yyy;
			
			ii++;
		} 
		answer = (vb-va)/2.0*summ;
	} else {
		//USANS so do trapezoidal integration
		int maxiter = 20;
		double tol = 1e-4;
		
		va=0;
		vb=fabs(i_sigq);
		
		//sprintf(buf, "i_sigq = %g, va = %g, vb = %g\r",i_sigq, va, vb);
		//XOPNotice("USANS Data. Great\r");
		//XOPNotice(buf);
		
		answer = qtrap_USANS(fi,pp,va,vb,tol,maxiter);
		answer /= vb;
	}
	
	
	p->result = answer;
	
	return 0;
	}

int Smear_Model_76_X(GenSmearParamsPtr p)
{
	PassParams pp;
	FunctionInfo fi;
	int badParameterNumber;
	int requiredParameterTypes[2];
	int err;
	double ans;
	//char buf[256];
	
	int ii;
	double nord,va,vb,summ,yyy,zi,Pi;
	double answer,Resoln,i_shad,i_qbar,i_sigq;

	//Get name of function into string here with
	char func[255];
	GetCStringFromHandle(p->funcname, func, sizeof(func));
	
	//Make sure function that we want to call exists
	//GetFunctionInfo(func,&fi);
	if (err = GetFunctionInfo(func,&fi)){
		//	if (err = GetFunctionInfo("Cyl_PolyRadiusX",&fi)){
		XOPNotice("Error at GetFunctionInfo\r");
		return err;
		}
	requiredParameterTypes[1] = NT_FP64;
	requiredParameterTypes[0] = WAVE_TYPE;
	if (err = CheckFunctionForm(&fi, 2, requiredParameterTypes, &badParameterNumber, NT_FP64)){
		XOPNotice("Error at CheckFunctionForm\r");
		return err;
	}

	
	Pi = 4.0*atan(1.0);
	
	i_shad = p->i_shad;
	i_qbar = p->i_qbar;
	i_sigq = p->i_sigq;
	
	//sprintf(buf, "i_shad = %g, i_qbar = %g, i_sigq = %g", i_shad, i_qbar, i_sigq);
	//XOPNotice(buf);
	
	pp.waveHandle = p->waveHandle;
	pp.x = p->x;
	//need interpolation
	
	if (i_sigq >= 0){
		
		nord = 20;
		va = -3*i_sigq + i_qbar;
		if (va < 0){
			va = 0;
		}
		vb = 3*i_sigq + i_qbar;
		
		summ = 0.0;
		ii=0;
		while (ii < nord) {
			zi = (Gauss76Z[ii]*(vb-va) + va + vb)/2.0;
			pp.x = zi;
			Resoln = i_shad/sqrt(2*Pi*i_sigq*i_sigq);
			Resoln *= exp((-1*pow((zi-i_qbar),2))/(2*i_sigq*i_sigq));
			if (err = CallFunction(&fi, (void*)&pp, &ans)){
				XOPNotice("Error at CallFunction in Gaussian Smear\r");
				return err;
			}
			//			CallFunction(&fi, (void*)&pp, &ans);
			yyy = Gauss76Wt[ii]*Resoln*ans;
			summ += yyy;
			
			ii++;
		} 
		answer = (vb-va)/2.0*summ;
	} else {
		//USANS so do trapezoidal integration
		int maxiter = 20;
		double tol = 1e-4;
		
		va=0;
		vb=fabs(i_sigq);
		
		//sprintf(buf, "i_sigq = %g, va = %g, vb = %g\r",i_sigq, va, vb);
		//XOPNotice("USANS Data. Great\r");
		//XOPNotice(buf);
		
		answer = qtrap_USANS(fi,pp,va,vb,tol,maxiter);
		answer /= vb;
	}
	
	
	p->result = answer;
	
	return 0;
	}


double
qtrap_USANS(FunctionInfo fi, PassParams p, double aa, double bb, double eps, int maxit){
	double olds,ss;
	double xx,tnm,summ,del,arg1,arg2,ans;
	int it,jj,kk;
	int err;
	
	//char buf[256];
	
	double qval = p.x;
	double temp = 0;
	
	//XOPNotice("In qtrap_USANS\r");
	
	olds = -1e-30;
	for (jj = 1; jj <= maxit; jj++){
		
		if (jj == 1){
			arg1 = pow(qval,2)+pow(aa,2);
			arg2 = pow(qval,2)+pow(bb,2);
			p.x = sqrt(arg1);
			if (err = CallFunction(&fi, (void*)&p, &ans)){
				XOPNotice("Error at 1st CallFunction in qtrap\r");
			}
			temp = ans;
			p.x = sqrt(arg2);
			CallFunction(&fi, (void*)&p, &ans);
			temp += ans;
			ss = 0.5*(bb-aa)*temp;
			//sprintf(buf, "jj = 1: aa = %g, bb = %g, temp = %g, ss = %g\r", aa, bb, temp, ss);
			//XOPNotice(buf);
		} else {
			it = pow(2,jj-2);
			tnm = (double)it;
			del = (bb-aa)/tnm;
			xx = aa+(0.5*del);
			summ = 0;
			for (kk = 1; kk <= it; kk++){
				arg1 = pow(qval,2)+pow(xx,2);
				p.x = sqrt(arg1);
				if (err = CallFunction(&fi, (void*)&p, &ans)){
					XOPNotice("Error at 2nd CallFunction in qtrap\r");
				}
				summ += ans;
				xx += del;
			}
			ss = 0.5*(ss+(bb-aa)*summ/tnm);
			//sprintf(buf, "jj = %d: arg1 = %g, summ = %g, tnm= %g, ss = %g\r", jj, arg1, summ, tnm, ss);
			//XOPNotice(buf);
		}
		
		//sprintf(buf,"ss = %g\r",ss);
		//XOPNotice(buf);
		
		//		ss = trapzd_USANS(fi,p,aa,bb,jj);
		if ( fabs(ss-olds) < eps*fabs(olds))
			return ss;
		if ( (ss == 0.0) && (olds == 0.0) && (jj > 6) ) // no progress?
			return ss;
		olds = ss;
	}
	
	XOPNotice("Maxit exceeded in qtrap. If you're here, there was a problem in qtrap");
	return (ss); // should never get here if function is well behaved
	
}

//static double
//trapzd_USANS(FunctionInfo fi, PassParams p, double aa, double bb, int nn){
//	double xx,tnm,summ,del,arg1,arg2,ans;
//	int it,jj;
//	
//	static double sval;
//	
//	double qval = p.x;
//	double temp = 0;
//
//	//XOPNotice("In trapzd_USANS\r");
//
//	if (nn == 1){
//		arg1 = pow(qval,2)+pow(aa,2);
//		arg2 = pow(qval,2)+pow(bb,2);
//		p.x = arg1;
//		CallFunction(&fi, (void*)&p, &ans); 
//		p.x = arg2;
//		temp = ans;
//		CallFunction(&fi, (void*)&p, &ans);
//		temp += ans;
//		sval = 0.5*(bb-aa);
//		return sval;
//	} else {
//		it = pow(2,nn-2);
//		tnm = it;
//		del = (bb-aa)/tnm;
//		xx = aa+0.5*del;
//		summ = 0;
//		for (jj = 1; jj <= it; jj++){
//			arg1 = pow(qval,2)+pow(xx,2);
//			p.x = arg1;
//			CallFunction(&fi, (void*)&p, &ans);
//			summ += ans;
//			xx += del;
//		}
//		sval = 0.5*(sval+(bb-aa)*summ/tnm);
//		return sval;
//	}
//	
//
//}

int
SmearedCyl_PolyRadiusX(SmearParamsPtr p)
{
	double* dp;
	double q;
	double ans;

	int ii;
	double nord,va,vb,summ,yyy,zi,Pi;
	double answer,Resoln,i_shad,i_qbar,i_sigq;
//	char buf[256];
	
	Pi = 4.0*atan(1.0);
	i_shad = p->i_shad;
	i_qbar = p->i_qbar;
	i_sigq = p->i_sigq;
	
	dp = WaveData(p->waveHandle);
	q = p->x;
	
	p->result = Cyl_PolyRadius(dp,q);
	return 0;
	
	if (i_sigq >= 0){
		
		nord = 20;
		va = -3*i_sigq + i_qbar;
		if (va < 0){
			va = 0;
		}
		vb = 3*i_sigq + i_qbar;
		summ = 0.0;
		ii=0;
		while (ii < nord) {
			zi = (Gauss20Z[ii]*(vb-va) + va + vb)/2.0;
			q = zi;
			Resoln = i_shad/sqrt(2*Pi*i_sigq*i_sigq);
			Resoln *= exp((-1*pow((zi-i_qbar),2))/(2*i_sigq*i_sigq));
			ans = Cyl_PolyRadius(dp,q);
			yyy = Gauss20Wt[ii]*Resoln*ans;
			summ += yyy;
			
			ii++;
		} 
		answer = (vb-va)/2.0*summ;
	} else {
		//USANS so do trapezoidal integration
		//int maxiter = 20;
		//double tol = 1e-4;
		
		//va=0;
		//vb=fabs(i_sigq);
		
		//sprintf(buf, "i_sigq = %g, va = %g, vb = %g\r",i_sigq, va, vb);
		//XOPNotice("USANS Data. Great\r");
		//XOPNotice(buf);
		
		//answer = qtrap_USANS(fi,pp,va,vb,tol,maxiter);
		//answer /= vb;
		
		//Just return a value that is clearly nonsense, but is non-zero
		//USANS Smearing code not in form suitable for this test of direct calling
		//of C library function. AJJ May 9 2007
		answer = -10;
	}
	p->result = answer;
	
	return 0;
}

