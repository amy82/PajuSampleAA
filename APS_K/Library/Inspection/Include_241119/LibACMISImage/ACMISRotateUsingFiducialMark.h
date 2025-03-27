/*
************************************************************************************************************************
*                                            Rotate angle(degree) algorithm
*
*                                     (c) Copyright 2018, LG Innotek. All rights reserved.
*
*                                     header of Rotate angle(degree) using fiducial mark DLL
*
* File    : ACMISRotateUsingFiducialMark.h
* Author  : seung-hwan SONG (shsonga@lginnotek.com)
* Version : V1.2.0
************************************************************************************************************************
*/

/* Change log:
- Version : V1.0.0
As from 2018/03/28
New.
- Version : V1.1.0
As from 2018/04/05
1) changed getAlgorithmVer() return type
   : std::string -> char*
- Version : V1.2.0
As from 2018/04/12
1) added
   : return error msg (ERROR_ROTATION_MSG)
2) changed
   : getAngle() return 'angle' sign 
     clockwise : '-'
     anti clockwise : '+'
*/

#pragma once

#include <iostream>
#include "export.h"

namespace RotateUsingFiducialMark
{
	typedef enum
	{
		ERROR_DIVIDE_BY_ZERO = -1,
		ERROR_NO_ERROR = 0
	} ERROR_ROTATION_MSG;

	//   fiducial mark position
	//    *Point 1(left)       *Point 2(right)

	class ACMISIMAGE_API CACMISRotateUsingFiducialMark
	{
	public:
		CACMISRotateUsingFiducialMark();
		virtual ~CACMISRotateUsingFiducialMark();

		/** \brief : get angle(degree) calculated from two points, *Point 1(left) *Point 2(right)
		* \author : seung-hwan SONG (shsonga@lginnotek.com)
		* \date : 2018/04/12
		*
		* \param :
		*        1) int pointX1, int pointY1, int pointX2, int pointY2 : x, y points. *Point 1(left) *Point 2(right)
		*        2) double pi : ¥ð, the circular constant
		*        3) double& angle : angle(degree) calculated from two points, *Point 1(left) *Point 2(right)
		*                           sign : clockwise '-',  anti clockwise '+'
		*
		* \return : ERROR_ROTATION_MSG
		*
		*/
		ERROR_ROTATION_MSG getAngle(int pointX1, int pointY1, int pointX2, int pointY2, double pi, double& angle) const;

		/** \brief : get algorithm version
		* \author : seung-hwan SONG (shsonga@lginnotek.com)
		* \date : 2018/04/05
		*
		* \param : void
		* \return : algorithm version(char*)
		*
		*/
		char* getAlgorithmVer() const;
	};
}

/*
DLL test code

RotateUsingFiducialMark::CACMISRotateUsingFiducialMark rotate;

char* algorithmVer;
algorithmVer = rotate.getAlgorithmVer();
cout << "algorithmVer ver : " << algorithmVer << endl;
// algorithmVer ver : 1.2.0

#if 1
// ex) sign '+' angle
int pointX1 = 404;
int pointY1 = 202;
int pointX2 = 861;
int pointY2 = 201;
int pointX3 = 399;
int pointY3 = 535;
int pointX4 = 868;
int pointY4 = 534;
#endif

#if 0
// ex) sign '-' angle

int pointX1 = 404;
int pointY1 = 202;
int pointX2 = 861;
int pointY2 = 203;
int pointX3 = 399;
int pointY3 = 535;
int pointX4 = 868;
int pointY4 = 536;
#endif
double angle = 0;

RotateUsingFiducialMark::ERROR_ROTATION_MSG result = RotateUsingFiducialMark::ERROR_NO_ERROR;

result = rotate.getAngle(pointX1, pointY1, pointX2, pointY2, CV_PI, angle);
if (result == RotateUsingFiducialMark::ERROR_NO_ERROR)
cout << "angle(degree) : " << angle << endl;
// angle1(degree) : 0.125373
else if (result == RotateUsingFiducialMark::ERROR_DIVIDE_BY_ZERO)
cout << "devide by zero" << endl;
else
cout << "unknown result : " << result  << endl;

result = rotate.getAngle(pointX3, pointY3, pointX4, pointY4, CV_PI, angle);
if (result == RotateUsingFiducialMark::ERROR_NO_ERROR)
cout << "angle(degree) : " << angle << endl;
// angle1(degree) : 0.122166
else if (result == RotateUsingFiducialMark::ERROR_DIVIDE_BY_ZERO)
cout << "devide by zero" << endl;
else
cout << "unknown result : " << result << endl;
*/

