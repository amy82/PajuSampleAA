/*
************************************************************************************************************************
*                                            Mechanical Optical Center algorithm
*
*                                     (c) Copyright 2018, LG Innotek. All rights reserved.
*
*                                     header of Mechanical Optical Center algorithm DLL
*
* File    : ACMISMechanicalOpticalCenter.h
* Author  : seung-hwan SONG (shsonga@lginnotek.com)
* Version : V1.1.1
************************************************************************************************************************
*/

/* Change log:
- Version : V1.0.0
As from 2018/03/28
New.
- Version : V1.1.0
As from 2018/04/05
1) changed 
   getAlgorithmVer() return type
   : std::string -> char*
2) changed
   getDistanceFromImageCenter()
   : xDistance = principalX - idealCenterX
     yDistance = principalY - idealCenterY
- Version : V1.1.1
As from 2018/04/12
1) added
   : return error msg (ERROR_MECHANICAL_OC_MSG)
*/

#pragma once

#include <iostream>
#include "export.h"

namespace MechanicalOpticalCenter
{
	typedef enum
	{
		ERROR_ERROR = -1,
		ERROR_NO_ERROR = 0
	} ERROR_MECHANICAL_OC_MSG;

	//   fiducial mark position
	//    *center

	class ACMISIMAGE_API CACMISMechanicalOpticalCenter
	{
	public:
		CACMISMechanicalOpticalCenter();
		virtual ~CACMISMechanicalOpticalCenter();

		/** \brief : get horizontal(x) and vertical(y) differences between the center of the image's center and the measured center(from fiducial mark)
		* \author : seung-hwan SONG (shsonga@lginnotek.com)
		* \date : 2018/04/05
		*
		* \param :
		*        1) int idealCenterX, int idealCenterY : ideal optical center X, Y. ex)1280, 1080
		*        2) int principalX, int principalY  : fiducial mark's center
		*        3) int& xDistance, int& yDistance  : ideal optical center X and ideal optical center Y differences
		*           between the center of the ideal optical center X,Y and the measured center(from fiducial mark)
		*           : xDistance = principalX - idealCenterX
		*           : yDistance = principalY - idealCenterY
		*
		* \return : ERROR_MECHANICAL_OC_MSG
		*
		*/
		ERROR_MECHANICAL_OC_MSG getDistanceFromImageCenter(int idealCenterX, int idealCenterY, int principalX, int principalY, int& xDistance, int& yDistance) const;

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

MechanicalOpticalCenter::CACMISMechanicalOpticalCenter oc;

char * algorithmVer;
algorithmVer = oc.getAlgorithmVer();
cout << "algorithm ver : " << algorithmVer << endl;
// algorithm ver : 1.1.1

int idealCenterX = 640;
int idealCenterY = 540;
int principalX = 636;
int principalY = 538;
int xDistance = 0;
int yDistance = 0;

//xDistance = principalX - idealCenterX
//yDistance = principalY - idealCenterY
oc.getDistanceFromImageCenter(idealCenterX, idealCenterY, principalX, principalY, xDistance, yDistance);
cout << "xDistance : " << xDistance << "," << " yDistance : " << yDistance << endl;
// xDistance : -4, yDistance : -2
*/
