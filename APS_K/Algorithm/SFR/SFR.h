#pragma once
#include <math.h>

#define ALPHA  1
#define PI 3.141592653589793f

class CSFR
{
public:
	double* temp;
	double* shifts;
	double* edgex;
	double* Signal;
	double* AveEdge;
	double* AveTmp;
	double*	farea;
	long*   counts;

public:
	CSFR(void);
	~CSFR(void);

	short SFR_Processing(double* FreqHdl, double* dispString  , double* buf , long size_x , long size_y,  double CCD_Size, int iFlag_Freq, double dGain = 1.0);
	void AllocMemory(unsigned long size_x , unsigned long size_y);
	void FreeMemory(unsigned long size_x , unsigned long size_y);
	void Image_Transfose(double* src , double* dst, int width, int height);
	unsigned short Check_Image(double* farea, double* tmp, unsigned long size_x , unsigned long size_y);
	unsigned short locate_centroids(double* farea, double*  temp, double* shifts , unsigned long size_x , unsigned long size_y);
	unsigned short  Line_Fit(unsigned long ndata, double* x, double* y, double *b);
	unsigned short bin_to_regular_xgrid(unsigned short * alpha, double* edgex, double* Signal, 
		double* AveEdge, long* counts, unsigned long size_x , unsigned long size_y);
	void calculate_derivative(unsigned short alpha, double* AveTmp, double* AveEdge , unsigned long size_x , unsigned long size_y);
	void locate_max_PSF(unsigned short alpha, double* AveEdge, long size_x, long *pcnt2);
	void apply_hamming_window(unsigned short alpha, unsigned short newxwidth, double* AveEdge, long *pcnt2 , long size_x , long size_y);
	unsigned short FFT_Transform(long number, double *dx, double* lsf, long ns, double *ds, double* sfr);
};

