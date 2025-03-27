////#include "stdafx.h"
//#include <iostream>
//
////#include <C:\OpenCV\build\include\opencv2\highgui\highgui.hpp>
////#include <C:\OpenCV\build\include\opencv2\imgproc\imgproc.hpp>
////#include <C:\OpenCV\build\include\opencv2\calib3d\calib3d.hpp>
//
//const double w5 = 0.002118902;
//
//const float imageWidth5 = 1280;
//const float imageHeight5 = 960;

//cv::vector<cv::Point2f> undistort(cv::Size boardSize, cv::vector<cv::Point2f> pointBuf, cv::Point2f distortionCenter, double w)
//{
//	cv::vector<cv::Point2f> undistortedCoordinates;
//
//	for(int i = 0; i < boardSize.width * boardSize.height; i++)
//	{
//		cv::Point2f cartesianCoordinates = pointBuf.at(i) - distortionCenter;
//
//		double rd = sqrt(std::pow(cartesianCoordinates.x, 2) + std::pow(cartesianCoordinates.y, 2));
//		double ru = tan(rd * w) / (2 * tan(w / 2.0));
//
//		cartesianCoordinates *= (float)(ru / rd);
//
//		undistortedCoordinates.push_back(cartesianCoordinates + distortionCenter);
//	}
//
//	return undistortedCoordinates;
//}
//
//double calcChiSquareRow(cv::Size boardSize, cv::vector<cv::Point2f> pointBuf)
//{
//	double sum_xSquare;
//	double sum_x;
//	double sum_xy;
//	double sum_ySquare;
//	double sum_y;
//
//	double a, b, c, alpha, beta, sin_theta, cos_theta;
//	double chi_square;
//	double sum_chi_square = 0;
//
//	for (int row = 0; row < boardSize.height; row+=2)
//	{
//		sum_xSquare = 0;
//		sum_x = 0;
//		sum_xy = 0;
//		sum_ySquare = 0;
//		sum_y = 0;
//
//		for (int col = 0; col < boardSize.width; col++)
//		{
//			sum_xSquare += std::pow(pointBuf.at(col + row * boardSize.width).x, 2);
//			sum_x += pointBuf.at(col + row * boardSize.width).x;
//			sum_xy += pointBuf.at(col + row * boardSize.width).x * pointBuf.at(col + row * boardSize.width).y;
//			sum_ySquare += std::pow(pointBuf.at(col + row * boardSize.width).y, 2);
//			sum_y += pointBuf.at(col + row * boardSize.width).y;
//		}
//
//		a = sum_xSquare - (std::pow(sum_x, 2) / boardSize.width);
//		b = sum_xy - ((sum_x * sum_y) / boardSize.width);
//		c = sum_ySquare - (std::pow(sum_y, 2) / boardSize.width);
//		alpha = a - c;
//		beta = alpha / ( 2 * sqrt( std::pow(alpha, 2) + (4 * std::pow(b, 2)) ) );
//		sin_theta = sqrt(0.5 - beta);
//		cos_theta = sqrt(0.5 + beta);
//
//		chi_square = (a * std::pow(sin_theta, 2)) - (2 * std::abs(b) * std::abs(sin_theta) * cos_theta) + (c * std::pow(cos_theta, 2));
//		sum_chi_square += chi_square;
//	}
//
//	return sum_chi_square;
//}
//
//double calcChiSquareCol(cv::Size boardSize, cv::vector<cv::Point2f> pointBuf)
//{
//	double sum_xSquare;
//	double sum_x;
//	double sum_xy;
//	double sum_ySquare;
//	double sum_y;
//
//	double a, b, c, alpha, beta, sin_theta, cos_theta;
//	double chi_square;
//	double sum_chi_square = 0;
//
//	for (int col = 0; col < boardSize.width; col+=2)
//	{
//		sum_xSquare = 0;
//		sum_x = 0;
//		sum_xy = 0;
//		sum_ySquare = 0;
//		sum_y = 0;
//
//		for (int row = 0; row < boardSize.height; row++)
//		{
//			sum_xSquare += std::pow(pointBuf.at(col + row * boardSize.width).x, 2);
//			sum_x += pointBuf.at(col + row * boardSize.width).x;
//			sum_xy += pointBuf.at(col + row * boardSize.width).x * pointBuf.at(col + row * boardSize.width).y;
//			sum_ySquare += std::pow(pointBuf.at(col + row * boardSize.width).y, 2);
//			sum_y += pointBuf.at(col + row * boardSize.width).y;
//		}
//
//		a = sum_xSquare - (std::pow(sum_x, 2) / boardSize.height);
//		b = sum_xy - ((sum_x * sum_y) / boardSize.height);
//		c = sum_ySquare - (std::pow(sum_y, 2) / boardSize.height);
//		alpha = a - c;
//		beta = alpha / ( 2 * sqrt( std::pow(alpha, 2) + (4 * std::pow(b, 2)) ) );
//		sin_theta = sqrt(0.5 - beta);
//		cos_theta = sqrt(0.5 + beta);
//
//		chi_square = (a * std::pow(sin_theta, 2)) - (2 * std::abs(b) * std::abs(sin_theta) * cos_theta) + (c * std::pow(cos_theta, 2));
//		sum_chi_square += chi_square;
//	}
//
//	return sum_chi_square;
//}
//
//cv::Point2f evaluateDistortionCenter(cv::Size boardSize, cv::vector<cv::Point2f> pointBuf, const double alpha, const double beta, const double gamma)
//{
//	cv::Point2f returnDC;
//
//	double resultCol, resultRow;
//
//	int ilo, ihi, inhi;
//	float fac, fac1, fac2;
//
//	cv::Point2f simplexPc, simplexPsum, simplexPs, simplexPss;
//	double simplexYs, simplexYsave;
//
//	cv::vector<cv::Point2f> simplexP;
//	cv::vector<double> simplexY;
//
//	cv::vector<cv::Point2f> undistortedPointBuf;
//
//	const int offset = 30;
//	simplexP.push_back(cv::Point2f(imageWidth / 2, imageHeight / 2 - offset));
//	simplexP.push_back(cv::Point2f((imageWidth / 2) - (0.85 * offset), (imageHeight / 2) + (0.5 * offset)));
//	simplexP.push_back(cv::Point2f((imageWidth / 2) + (0.85 * offset), (imageHeight / 2) + (0.5 * offset)));
//
//	undistortedPointBuf = undistort(boardSize, pointBuf, simplexP.at(0), w);
//	resultCol = calcChiSquareCol(boardSize, undistortedPointBuf);
//	resultRow = calcChiSquareRow(boardSize, undistortedPointBuf);
//	simplexY.push_back(resultCol + resultRow);
//
//	undistortedPointBuf = undistort(boardSize, pointBuf, simplexP.at(1), w);
//	resultCol = calcChiSquareCol(boardSize, undistortedPointBuf);
//	resultRow = calcChiSquareRow(boardSize, undistortedPointBuf);
//	simplexY.push_back(resultCol + resultRow);
//
//	undistortedPointBuf = undistort(boardSize, pointBuf, simplexP.at(2), w);
//	resultCol = calcChiSquareCol(boardSize, undistortedPointBuf);
//	resultRow = calcChiSquareRow(boardSize, undistortedPointBuf);
//	simplexY.push_back(resultCol + resultRow);
//
//
//	for (int ii = 0; ii < 500; ii++)
//	{
//		ilo = 0;
//
//		ihi = simplexY.at(0) > simplexY.at(1) ? (inhi = 1, 0) : (inhi = 0, 1);
//		for (int i = 0; i < 3; i++)
//		{
//			if (simplexY.at(i) <= simplexY.at(ilo))
//			{
//				ilo = i;
//			}
//
//			if (simplexY.at(i) > simplexY.at(ihi))
//			{
//				inhi = ihi;
//				ihi = i;
//			}
//			else if (simplexY.at(i) > simplexY.at(inhi) && i != ihi)
//			{
//				inhi = i;
//			}
//		}
//		//
//		returnDC = simplexP.at(ilo);
//
//		simplexPsum = simplexP.at(0) + simplexP.at(1) + simplexP.at(2);
//		simplexPc = (1/3) * simplexPsum;
//
//		fac = alpha;//-1.0;
//		fac1 = (1.0-fac)/2;
//		fac2 = fac1 - fac;
//		simplexPs = fac1 * simplexPsum - fac2 * simplexP.at(ihi);
//		undistortedPointBuf = undistort(boardSize, pointBuf, simplexPs, w);
//		resultCol = calcChiSquareCol(boardSize, undistortedPointBuf);
//		resultRow = calcChiSquareRow(boardSize, undistortedPointBuf);
//		simplexYs = resultCol + resultRow;
//
//		if(simplexYs < simplexY.at(ihi))
//		{
//			simplexY.at(ihi) = simplexYs;
//			simplexP.at(ihi) = simplexPs;
//			simplexPsum = simplexP.at(0) + simplexP.at(1) + simplexP.at(2);
//		}
//		if(simplexYs <= simplexY.at(ilo))
//		{
//			fac = beta;//2.0;
//			fac1 = (1.0-fac)/2;
//			fac2 = fac1 - fac;
//			simplexPs = fac1 * simplexPsum - fac2 * simplexP.at(ihi);
//			undistortedPointBuf = undistort(boardSize, pointBuf, simplexPs, w);
//			resultCol = calcChiSquareCol(boardSize, undistortedPointBuf);
//			resultRow = calcChiSquareRow(boardSize, undistortedPointBuf);
//			simplexYs = resultCol + resultRow;
//
//			if(simplexYs < simplexY.at(ihi))
//			{
//				simplexY.at(ihi) = simplexYs;
//				simplexP.at(ihi) = simplexPs;
//				simplexPsum = simplexP.at(0) + simplexP.at(1) + simplexP.at(2);
//			}
//		}
//		else if(simplexYs >= simplexY.at(inhi))
//		{
//			simplexYsave = simplexY.at(ihi);
//			fac = gamma;//0.5;
//			fac1 = (1.0-fac)/2;
//			fac2 = fac1 - fac;
//			simplexPs = fac1 * simplexPsum - fac2 * simplexP.at(ihi);
//			undistortedPointBuf = undistort(boardSize, pointBuf, simplexPs, w);
//			resultCol = calcChiSquareCol(boardSize, undistortedPointBuf);
//			resultRow = calcChiSquareRow(boardSize, undistortedPointBuf);
//			simplexYs = resultCol + resultRow;
//
//			if(simplexYs < simplexY.at(ihi))
//			{
//				simplexY.at(ihi) = simplexYs;
//				simplexP.at(ihi) = simplexPs;
//				simplexPsum = simplexP.at(0) + simplexP.at(1) + simplexP.at(2);
//			}
//			if(simplexYs >= simplexYsave)
//			{
//				for(int i = 0; i < 3 ; i++)
//				{
//					if(i != ilo)
//					{
//						simplexP.at(i) = 0.5 * (simplexP.at(i) + simplexP.at(ilo));
//						undistortedPointBuf = undistort(boardSize, pointBuf, simplexP.at(i), w);
//						resultCol = calcChiSquareCol(boardSize, undistortedPointBuf);
//						resultRow = calcChiSquareRow(boardSize, undistortedPointBuf);
//						simplexY.at(i) = resultCol + resultRow;
//					}
//				}
//				simplexPsum = simplexP.at(0) + simplexP.at(1) + simplexP.at(2);
//			}
//		}
//
//	}
//
//	return returnDC;
//}
//
//bool getDistortionCenter(cv::Mat src,cv::Point2f dc)
//{
//	cv::Mat src_gray;
//	cv::Mat distortionPatchRoiT, distortionPatchRoiT_threshold;
//	cv::Mat distortionPatchRoiB, distortionPatchRoiB_threshold;
//
////	src = cv::imread(argv[argc-1]);
//	cv::cvtColor(src, src_gray, CV_BGR2GRAY);
//
//	distortionPatchRoiT = src_gray(cv::Rect(320, 140, 640, 320));
//	distortionPatchRoiB = src_gray(cv::Rect(320, 500, 640, 320));
//
//	cv::threshold(distortionPatchRoiT, distortionPatchRoiT_threshold, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
//	cv::threshold(distortionPatchRoiB, distortionPatchRoiB_threshold, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
//
//	cv::Size boardSizeT = cv::Size(13, 4);//cv::Size(13, 6);
//	cv::Size boardSizeB = cv::Size(13, 4);//cv::Size(13, 6);
//	cv::Size boardSize = cv::Size(13, 8);//cv::Size(13, 12);
//
//	cv::vector<cv::Point2f> pointBufT;
//	cv::vector<cv::Point2f> pointBufB;
//	cv::vector<cv::Point2f> pointBuf;
//
//	bool found1 = cv::findCirclesGrid(distortionPatchRoiT_threshold, boardSizeT, pointBufT);
//	bool found2 = cv::findCirclesGrid(distortionPatchRoiB_threshold, boardSizeB, pointBufB);
//
//	if(found1 && found2)
//	{
//		for(int i = 0; i < boardSizeT.height * boardSizeT.width; i++)
//		{
//			pointBufT.at(i) += cv::Point2f(320, 140);
//			pointBufB.at(i) += cv::Point2f(320, 500);
//		}
//
//		pointBuf.reserve(pointBufT.size() + pointBufB.size());
//		pointBuf.insert(pointBuf.end(), pointBufT.begin(), pointBufT.end());
//		pointBuf.insert(pointBuf.end(), pointBufB.begin(), pointBufB.end());
//
//		const float alpha = -1.0f;
//		const float beta = 2.0f;
//		const float gamma = 0.5f;
//
//		dc = evaluateDistortionCenter(boardSize, pointBuf, alpha, beta, gamma);
//		
//		std::cout << "(" << dc.x << ", " << dc.y << ")" << std::endl;
//	}
//
//	return 0;
//}
