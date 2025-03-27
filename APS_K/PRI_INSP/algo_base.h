#ifndef _ALGO_BASE_H
#define _ALGO_BASE_H

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <map>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iterator>
#include <regex>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <WinGDI.h>		// for POINTFLOAT

#pragma comment (lib,"winmm.lib")
#pragma warning(disable: 4244 4819 4996) 

using namespace std;
using namespace std::tr1;

/*test pattern for debug*/
#define  BAD_INT		-1234567890
#define  BAD_DOUBLE		-1234567890.0 
#define  BAD_STRING		"-1234567890" 

//namespace algo_base // algo_base
//{


struct MapContent
{	
	int i;  double d; string s;

	MapContent(): i(BAD_INT),d(BAD_DOUBLE),s(BAD_STRING){}; 
	operator int() {assert(i!=BAD_INT); return i;}
	operator double() {assert(d!=BAD_DOUBLE); return d;}
	operator string() {assert(s!=BAD_STRING); return s;}

	int& operator=(int a)		{assert(get_t()==CON_INT); i=a;return i;}
	double& operator=(double a)	{assert(get_t()==CON_DBL); d=a;return d;}
	string& operator=(string a)	{assert(get_t()==CON_STR); s=a;return s;}

	enum tCONTENT {CON_INT,CON_DBL,CON_STR};
	void set_t(tCONTENT type) {content_type_= type;};
	tCONTENT get_t() {return content_type_;};

private:
	tCONTENT content_type_;
};

class CMapData 
{
public:
	typedef map<string,MapContent> Map;
	MapContent &operator[](std::string key)
	{	
		auto it=map_.find(key);
		if(it == map_.end()) /*new item*/
		{
			MapContent &data= map_[key];
			smatch sm;
			regex ex(".*\\.([ids])"); /*tag pattern*/
			if(regex_match(key,sm,ex))
			{
				if(sm[1].str()=="i") {
					data.set_t(MapContent::CON_INT);
				} else if(sm[1].str()=="d") {
					data.set_t(MapContent::CON_DBL);
				} else if(sm[1].str()=="s") {
					data.set_t(MapContent::CON_STR);
				} else assert(0);
			} else assert(0);

			key_.push_back(key);
			return data;
		}
		return (*it).second;
	}

	void clear(void)
	{
		map_.clear();
		key_.clear();
	}

	bool is_empty()
	{
		return key_.capacity() != 0 ? false : true;
	}

	vector<string>::iterator vbegin(void) /*vector<string> iterator*/
	{
		return key_.begin();
	}

	vector<string>::iterator vend(void)
	{
		return key_.end();
	}

	map<string,MapContent>::iterator mbegin(void) /*map<string,MapContent> iterator*/
	{
		return map_.begin();
	}

	map<string,MapContent>::iterator mend(void)
	{
		return map_.end();
	}

private:	
	map<string,MapContent> map_;
	vector<string> key_;
};

//////////////////////////////////////////////////////////////////
// field position data class
//////////////////////////////////////////////////////////////////

#define CALC_FIELD_POS	4
#define CALC_CENTER_POS	CALC_FIELD_POS

class CFieldPos
{
public:
	CFieldPos(int w, int h, float field) 
	{
		for (int i=0; i<CALC_FIELD_POS; i++) pt[i].x = pt[i].y = 0.0;
		if (field < 0.0 || field > 1.0) return;

		float diagonal = sqrtf((w*w+h*h));
		float length = field*diagonal/2.0;
		float theta = atan2f(h, w);
		float cx = (float)w/2.0; center.x = (int)cx;
		float cy = (float)h/2.0; center.y = (int)cy;

		pt[0].x = cx - length*cosf(theta); pt[0].y = cy - length*sinf(theta);
		pt[1].x = cx + length*cosf(theta); pt[1].y = cy - length*sinf(theta);
		pt[2].x = cx - length*cosf(theta); pt[2].y = cy + length*sinf(theta);
		pt[3].x = cx + length*cosf(theta); pt[3].y = cy + length*sinf(theta);

		for (int i=0; i<CALC_FIELD_POS; i++)
		{
			TRACE("%.3lf, %.3lf\n", pt[i].x, pt[i].y);
		}
	};
	virtual ~CFieldPos(void) {};

	void SetMaskRect(int masksize)
	{
		for (int i=0; i<CALC_FIELD_POS; i++)
		{
			rect[i].SetRect((int)((double)pt[i].x - (double)masksize/2.0), (int)((double)pt[i].y - (double)masksize/2.0), 
				            (int)((double)pt[i].x + (double)masksize/2.0), (int)((double)pt[i].y + (double)masksize/2.0));       
		}
		rect[CALC_CENTER_POS].SetRect((int)((double)center.x - (double)masksize/2.0), (int)((double)center.y - (double)masksize/2.0), 
								      (int)((double)center.x + (double)masksize/2.0), (int)((double)center.y + (double)masksize/2.0));       
	};

public:
	POINTFLOAT pt[CALC_FIELD_POS];
	CRect rect[CALC_FIELD_POS+1];
	CPoint center;
	double avg[CALC_FIELD_POS+1];
};
//////////////////////////////////////////////////////////////////


// By ckl [20140827]
//#define IMAGE_WIDTH 1280
//#define IMAGE_HEIGHT 964


class CPixelInfo
{
public:
	CPixelInfo() 
	{
	};

	virtual ~CPixelInfo(void) 
	{
	};

public:
	CRect **rect;    // Pixel 주변의 Mask 사이즈 영역
	double **m_dAvg; // 주변 Pixel 밝기의 평균값
	int **m_nBright; // Pixel의 밝기 값
	int **m_nResult; // 검사 결과
};
//////////////////////////////////////////////////////////////////


class CBlockInfo
{
public:
	CBlockInfo() 
	{
	};

	virtual ~CBlockInfo(void) 
	{
	};

public:
	CRect **rect;        // Block 영역(Block으로 구분한 경우의 영역정보)
	CRect **pixelrect;   // Pixel 영역(해당 Block의 실제 Pixel 영역 정보)
	double **m_dAvg;     // 주변 Pixel 밝기의 평균값
	double **m_dBright;  // Pixel의 밝기 값
	int **m_nResult;     // 검사 결과
	int **m_nAreaIndex;  // 해당 블럭이 어느 영역에 포함되어 있는지를 확인 하기 위한 변수
};


//////////////////////////////////////////////////////////////////
// duration time class
//////////////////////////////////////////////////////////////////
class CDuration
{
protected:
	LARGE_INTEGER m_liStart;
	LARGE_INTEGER m_liStop;

	LONGLONG m_llFrequency;
	LONGLONG m_llCorrection;

public:
	CDuration(void);

	void Start(void);
	void Stop(void);
	double GetDuration(void) const;
};
//////////////////////////////////////////////////////////////////

void GetIni(string file, CMapData &db, bool is_clear = true);

//} // algo_base

#endif
