#include "StdAfx.h"
#include "SFR.h"


CSFR::CSFR(void)
{
}


CSFR::~CSFR(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// By CDJung
// E-mail : jung1768@hanmail.net
// Phone : 010-3357-7748
// Date : 2013. 2. 4
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//! dGain : LG 이노텍 연구소와의 데이터와 맞추기 위한 Gain (손영탁 상무님 지시 사항, 2013/4/1)
short CSFR::SFR_Processing(double* FreqHdl, double* dispString  , double* buf, long size_x , long size_y,double CCD_Size, int iFlag_Freq, double dGain)
{
	unsigned short    i, j, nSamplesPerPixel, tmpalpha, err=0;
	long              pcnt, pcnt2, col, ww_in_pixels;
	double            dt,dtl,sfrc,tmp,tmp2,slope;

	if(size_x <=0 || size_y <=0) return 1;

	// Verify input selection dimensions are EVEN
	if(fmod((double)size_x,2.0) != 0.00)
		return 1;

	if(fmod((double)size_y,2.0) != 0.00) 
		return 1;



 	if (size_x > size_y)
 	{
 		long temp;
 		temp = size_x;
 		size_x = size_y;
 		size_y = temp;
 
 		ww_in_pixels = size_x;
 		// Allocate memory
 		AllocMemory(size_x , size_y);
 		Image_Transfose(buf , farea, size_y, size_x);
 	}
	else
	{
		ww_in_pixels = size_x;
		// Allocate memory
		AllocMemory(size_x , size_y);

		for(int m=0; m<size_y;m++)
		{
			for(int n=0; n<size_x;n++)
			{
				farea[m*size_x+n] = buf[m*size_x+n];
			}
		}
	}

	nSamplesPerPixel = 1;
	
	if(farea == NULL)
	{
		FreeMemory(size_x, size_y);
		return 1;
	}

	err = Check_Image(farea ,temp, size_x , size_y);		// 밝기 값 차이가 20이상 나는지 확인..
	
	
	if(err !=0) {
		FreeMemory(size_x, size_y);
		return 1;
	}

	err = locate_centroids(farea, temp, shifts , size_x , size_y);

	if(err !=0) {
		FreeMemory(size_x, size_y);
		return 1;
	}

	//Calculate the best fit line to the centroids
	err = Line_Fit(size_y , temp , shifts, &slope);
	if(err !=0) {
		FreeMemory(size_x, size_y);
		return 1;
	}

	if(fabs(slope) < (1.0/(double)size_y) || slope > (double)(1.0/4.0))
	{
		FreeMemory(size_x, size_y);
		return 1;
	}

	/* Figure out how many lines to use for size_y: new window will start at top and go down that number of lines< size_y
	such that an integer number of x-transitions are made by the edge; for example, if we had a slope of 10(the edge goes down 10
	lines before jumping over one pixel horizontally), and size_y = 35, the new size_y is going to be 30 (an integer multiple of
	10, less than 35). */

	size_y = (unsigned short)((long)(size_y*slope)*(1.0/slope)); //size_y : best fit line

	// reference the temp and shifts values to the new y center
	col = (long)size_y/2;
	for(i=0; i<size_y;i++)
	{
		temp[i] = (double)i - (double)col;
	}

	// Instead of using the values in shifts, synthesize new ones based on the best fit line.
	for(i=0; i<size_y;i++)
	{
		shifts[i] = slope * (temp[i]);
	}

	// compute the global MAX and MIN
	dt = 99999999.9;
	dtl = -99999999.9;

	pcnt = 0;
	for(j=0; j<size_y;j++) {
		for(i=0; i < size_x ; i++) {
			if (dt > farea[pcnt])
			{
				dt = farea[pcnt];
			}
			if (dtl < farea[pcnt])
			{
				dtl = farea[pcnt];
			}
			pcnt++;
		}
	}

	// Calculate a long paired list of x values and signal values
	pcnt = 0;
	for( j=0; j < size_y ; j++) {
		for (i=0; i < size_x ; i++) {
			edgex[pcnt] = (double)i - shifts[j];
			Signal[pcnt] = ((farea[((j*(long)size_x)+i)]) - dt)/(dtl-dt);
			pcnt++;
		}
	}

	tmpalpha = (unsigned short)ALPHA;
	err = bin_to_regular_xgrid(&tmpalpha, edgex, Signal, AveEdge, counts, size_x , size_y);
	if(err !=0) {
		FreeMemory(size_x, size_y);
		return 1;
	}

	calculate_derivative((unsigned short)ALPHA, AveTmp , AveEdge, size_x , size_y);

	locate_max_PSF((unsigned short)ALPHA, AveEdge, size_x, &pcnt2);

	apply_hamming_window((unsigned short)ALPHA, (unsigned short)ww_in_pixels, AveEdge, &pcnt2 , size_x , size_y);

	tmp = 1.0;
	tmp2 = 1.0/((double)size_x*ALPHA);

	// ftwos (nx,dx, lsf(x) , nf, df, sfr(f)
	(void)FFT_Transform((long)ALPHA*size_x , &tmp , AveEdge, (long)(size_x*ALPHA/2.0), &tmp2, AveTmp );
	
	switch(iFlag_Freq)
	{
	case 0:
		{
			for(i=0; i < (long)((double)size_x*ALPHA/2.0); i++) {
				sfrc = AveTmp[i];
				FreqHdl[i] = floor(1000*((double)i/(double)size_x)/CCD_Size);
				dispString[i] = ((double)(sfrc/AveTmp[0])) * dGain;
				if(dispString[i]>1.0) dispString[i] = 1.0;
			}
		}
		break;
	case 1:
		{
			for(i=0; i < (long)((double)size_x*ALPHA/2.0); i++) {
				FreqHdl[2*i] = (2*(double)i/(double)(size_x-1)) * CCD_Size;
				FreqHdl[2*i+1] = ((double)(2*i+1)/(double)(size_x-1)) * CCD_Size;
				dispString[2*i] = (AveTmp[i]/AveTmp[0]) * dGain;
				dispString[2*i+1] = ((AveTmp[i]+AveTmp[i+1])/(AveTmp[0] * 2.)) * dGain;

				if(dispString[2*i]>1.0) dispString[2*i] = 1.0;
				if(dispString[2*i+1]>1.0) dispString[2*i+1] = 1.0;
			} 
		}
		break;
	case 2:
		{			
			for(i=0; i < (long)((double)size_x*ALPHA/2.0); i++)
			{
				sfrc = AveTmp[i];
				FreqHdl[i] = CCD_Size * (double)i/ (double)size_x;
				dispString[i] = ((double)(sfrc/AveTmp[0])) * dGain;

				if(dispString[i]>1.0) dispString[i] = 1.0;
			}
		}
		break;
	}//! switch(iFlag_Freq)

	// I/O code calls here...
	FreeMemory(size_x, size_y);
	return (0);
}

void CSFR::Image_Transfose(double* src , double* dst, int width, int height)
{
	int i, j;

	for(i=0; i<height; i++) {
		for(j=0; j<width; j++) {
			dst[j*height + i] = src[i*width + j];
		}
	}
}


void CSFR::AllocMemory(unsigned long size_x , unsigned long size_y)
{
	farea = new double[size_x*size_y];
	memset(farea , 0 , sizeof(double)*size_x*size_y);
	temp = new double[size_x*size_y];
	memset(temp , 0 , sizeof(double)*size_x*size_y);
	shifts = new double[size_x*size_y];
	memset(shifts , 0 , sizeof(double)*size_x*size_y);
	edgex = new double[size_x*size_y];
	memset(edgex , 0 , sizeof(double)*size_x*size_y);
	Signal = new double[size_x*size_y];
	memset(Signal , 0 , sizeof(double)*size_x*size_y);
	AveEdge = new double[size_x*size_y];
	memset(AveEdge , 0 , sizeof(double)*size_x*size_y);
	AveTmp = new double[size_x*size_y];
	memset(AveTmp , 0 , sizeof(double)*size_x*size_y);
	counts = new long[size_x*size_y];
	memset(counts , 0 , sizeof(long)*size_x*size_y);
}

void CSFR::FreeMemory(unsigned long size_x , unsigned long size_y)
{
	delete [] farea;
	farea = NULL;
	delete [] temp;
	temp = NULL;
	delete [] shifts;
	shifts = NULL;
	delete [] edgex;
	edgex = NULL;
	delete [] Signal;
	Signal = NULL;
	delete [] AveEdge;
	AveEdge = NULL;
	delete [] AveTmp;
	AveTmp = NULL;
	delete [] counts;
	counts = NULL;
}

unsigned short CSFR::Check_Image(double* farea, double* tmp,unsigned long size_x , unsigned long size_y) 
{
	double dt, dt1, dt2, dt3;

	// --> check to make sure there is a clear black to white or white to black
	// transition on both the bottom and the top of the image
	// --> If there is not at lease 20% difference between th left and right sides of the
	// image box, return with an error of 5: calling program will display an error message.
	// --> If the transition left-> right is white ->black,flip the data left to right
	// (the rest of the routine assumes a black to white transition from left to right)

	// Get averages of 4 pixels in each corner of the input image 
	// upper right corner
	dt = (farea[size_x-1] + farea[size_x - 2] + farea[2*size_x-1] + farea[2*size_x-2])/4.0;

	// lower right corner
	dt1 = (farea[(size_x*size_y-1)] + farea[(size_x*size_y-2)] + farea[((size_y-1)*size_x-1)] + farea[((size_y-1)*size_x-2)])/4.0;

	// lower left corner
	dt2 = (farea[((size_y-1)*size_x)] + farea[((size_y-1)*size_x+1)] + farea[((size_y-2)*size_x)] + farea[((size_y-2)*size_x+1)])/4.0;

	// upper left corner
	dt3 = (farea[0]+farea[1]+farea[size_x]+farea[size_x+1])/4.0;

	// If there is not at least 20% difference between the left and right sides of the
	// image box, return with an error of 5: calling program will display an error message

	if(fabs(dt-dt3) < 20) return 1;;
	if(fabs(dt1-dt2) < 20) return 1;;

	return 0;
}


unsigned short CSFR::locate_centroids(double* farea, double*  temp, double* shifts , unsigned long size_x , unsigned long size_y)
{
	unsigned long i,j;
	double dt,dt1, dt2;

	// Compute the first difference on each line. Interpolate to find the centroid of the first derivatives.
	for(j=0; j < size_y; j++)
	{
		dt = 0.0;
		dt1 = 0.0;

		for(i=0; i < size_x-1; i++)
		{
			dt2 = farea[((j*(long)size_x)+i)+1] - farea[((j*(long)size_x)+i)];
			dt += dt2*(double)i;
			dt1 += dt2;
		}
		shifts[j] = dt/dt1;
	}

	// check again to be sure we aren't too close to an edge on the corners. If the
	// black to white transitions is closer than 2 pixels from either side of the
	// data box, return an error of 5; the calling program will display an error
	// message (the same one as if there were not a difference between the left and
	// right sides of the box)

	if(shifts[size_y-1] < 2)
	{
		return 2;
	}

	if(fabs(shifts[0]-size_x) < 2)
	{
		return 2;
	}

	// Reference shifts to the vertical center of the data box
	j =  size_y/2;
	dt = shifts[j];

	for(i=0; i < size_y ; i++)
	{
		temp[i] = (double)i - (double)j;
		shifts[i] -= dt;
	}

	return 0;
}

unsigned short  CSFR::Line_Fit(unsigned long ndata, double* x, double* y, double *b)
{
	unsigned long i;
	double        t,sxoss,sx=0.0,sy=0.0,st2=0.0,ss,sigdat,chi2,a,siga,sigb;

	*b =0;
	for(i=0; i<ndata; i++) {
		sx += x[i];
		sy += y[i];
	}
	ss = (double)ndata;
	sxoss=sx/ss;

	for(i=0; i < ndata; i++) {
		t = x[i] - sxoss;
		st2 += t*t;
		*b += t*y[i];
	}

	*b /= st2;          // slope
	a=(sy-sx*(*b))/ss;  // offset

	siga = sqrt((1.0 + sx*sx/(ss*st2))/ss);
	sigb = sqrt(1.0/st2);
	chi2 = 0.0;

	for(i=0; i < ndata; i++)
		chi2 += (y[i] - a - (*b) * x[i])*(y[i] - a - (*b) * x[i]);

	sigdat = sqrt(chi2/(ndata-2));
	siga *= sigdat;
	sigb *= sigdat;

	return 0;
}


/* Note: this part gets averages and puts them in a number of bins, equal to size_x times alpha. Next a
long check is done in case one bin gets no values put into it: if this is the case, it will keep checking previous
bins until it finds one with non-zero counts and will use that value as its current bin average. If the first
bin has zero counts the program checks bins in the forward rather than reverse direction. If, in any case,
the end of the array of bins is reached before finding a non-zero count, the program starts checking in the
opposite direction.  A bin with zero counts must be avoided because each bin will be divided by counts at the end. */
unsigned short CSFR::bin_to_regular_xgrid(unsigned short * alpha, double* edgex, double* Signal, 
	double* AveEdge, long* counts, unsigned long size_x , unsigned long size_y)
{
	unsigned long  i,j,k,bin_number;

	for(i=0; i < (size_x*(*alpha)); i++) {
		AveEdge[i] = 0;
		counts[i] = 0;
	}

	for( i=0; i < (size_x*(long)size_y); i++) {
		bin_number = (long)((*alpha)*(edgex[i]));
		if(bin_number >= 0) {
			if(bin_number <= (size_x*(*alpha) - 1)) {
				if(bin_number ==0) {
				}
				AveEdge[bin_number] = AveEdge[bin_number] + Signal[i];
				counts[bin_number] = (counts[bin_number])+1;
			}
		}
	}

	for(i=0; i < (size_x*(*alpha)); i++) {
		j =0;
		k = 1;
		if(counts[i] == 0) {
			if(i==0) {
				while(!j) {

					if(counts[i+k] != 0) {
						AveEdge[i] = AveEdge[i+k]/((double)counts[i+k]);
						j=1;
					}
					else {
						k++;
						break;
					}
				}
			}
			else {
				while(!j && ((i-k) >= 0)) {
					if(counts[i-k] != 0) {
						AveEdge[i] = AveEdge[i-k]/((double)counts[i-k]);
						j=1;
					}
					else {
						k++;
						break;
					}

					if((i-k) < 0 ) {
						k = 1;
						while (!j) {
							if(counts[i+k] != 0) {
								AveEdge[i] = AveEdge[i+k]/((double)counts[i+k]);
							}
							else {
								k++;
								break;
							}
						}
					}
				}
			}
		}
		else {
			AveEdge[i] = (AveEdge[i])/((double)counts[i]);
		}
	}
	return 0;
}


void CSFR::calculate_derivative(unsigned short alpha, double* AveTmp, double* AveEdge , unsigned long size_x , unsigned long size_y)
{
	unsigned long i;

	for(i=0; i < size_x * alpha; i++) AveTmp[i] = AveEdge[i];
	for(i=1 ; i < (size_x * alpha-1); i++) AveEdge[i] = (AveTmp[i+1] - AveTmp[i-1])/2.00;
	AveEdge[0] = AveEdge[1];
	AveEdge[size_x*alpha-1] = AveEdge[size_x*alpha-2];
}


void CSFR::locate_max_PSF(unsigned short alpha, double* AveEdge, long size_x, long *pcnt2)
{
	long i;
	double dt=0.0, dt_new=0.0;
	long scnt2 = 0L, left =-1L, right = -1L;

	// find maximin value in Point Spread Function array
	for(i=0; i < size_x*alpha; i++) {
		dt_new = fabs(AveEdge[i]);
		if(dt_new > dt) {
			(*pcnt2) = (long)i;
			dt = dt_new;
		}
	}

	// find leftmost and rightmost occurrence of maximum
	for(i=0; i < size_x*alpha; i++) {
		dt_new = fabs(AveEdge[i]);
		if( dt_new == dt) {
			if (left < 0) left = i;
			right = i;
		}
	}

	// find center of maxima 
	(*pcnt2) = (right+left)/2;
}


void CSFR::apply_hamming_window(unsigned short alpha, unsigned short newxwidth, double* AveEdge, long *pcnt2 , long size_x , long size_y)
{
	long    i,j,begin, end, edge_offset;
	double  sfrc;

	// Shift the AveEdge[i] vector to center the lsf in the transform window
	edge_offset = (*pcnt2) - (size_x * alpha/2);
	if(edge_offset != 0) {
		if(edge_offset < 0) {
			for(i=size_x*alpha-1; i > -edge_offset-1 ; i--) AveEdge[i] = (AveEdge[i+edge_offset]);
			for(i=0; i < -edge_offset; i++) AveEdge[i] = 0.00;  /*must be last operation */
		}
		else {
			for(i=0; i < size_x * alpha-edge_offset; i++) AveEdge[i] = (AveEdge[i+edge_offset]);
			for(i=size_x*alpha-edge_offset; i < size_x *alpha; i++) AveEdge[i] = 0.00;
		}
	}

	// Multiply the LSF data by a Hamming window of width NEWXWIDTH*alpha
	begin = (size_x*alpha/2)-(newxwidth*alpha/2);
	if(begin < 0) begin = 0;

	end = (size_x * alpha/2) + (newxwidth*alpha/2);
	if (end > size_x*alpha ) end = size_x*alpha;

	for(i=0; i < begin; i++) AveEdge[i] = 0.0;
	for(i=end; i < size_x *alpha; i++) AveEdge[i] = 0.0;

	for(i=begin, j= -newxwidth*alpha/2; i < end; i++,j++) {
		sfrc = 0.54 + 0.46*cos((PI*(double)j)/(newxwidth*alpha/2));
		AveEdge[i] = (AveEdge[i])*sfrc;
	}
}


unsigned short CSFR::FFT_Transform(long number, double *dx, double* lsf, long ns, double *ds, double* sfr)
{
	double a,b,twopi, g, *ind=NULL;
	long i,j;

	twopi = 2.0 * PI;
	for(j=0; j < ns; j++) {
		g = twopi * (*dx) * (*ds) * (double)j;
		for(i=0, a=0, b=0; i < number; i++) {
			a += lsf[i] * cos(g*(double)i);
			b += lsf[i] * sin(g*(double)i);
		}
		sfr[j] = sqrt(a*a + b*b);
	}

	return 0;
}