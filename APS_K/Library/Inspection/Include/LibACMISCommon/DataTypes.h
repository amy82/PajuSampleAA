/*
 * Author:
 *   HyeongCheol Kim <bluewiz96@gmail.com>
 *
 * Copyright (C) 2014 HyeongCheol Kim <bluewiz96@gmail.com>
 *
 * Released under GNU Lesser GPL, read the file 'COPYING' for more information
 */

#ifndef __DATA_TYPES_H__
#define __DATA_TYPES_H__

#ifndef M_PI
#define	M_PI		(3.1415926535897932384626433832795)
#endif

#include <math.h>
#include <wtypes.h>

struct DBPOINT
{
	double x;
	double y;
};
using LPDBPOINT = DBPOINT*;

struct COMPLEX
{
	double re;
	double im;
};

struct DSIZE
{
	double	width;
	double	height;
};

typedef struct _DBox2D
{
	DBPOINT center;
	DSIZE size;
	double angle;
	double saturation;
} DBox2D;

class CDPoint : public DBPOINT
{
public:
	// constructor
	CDPoint(double _x = 0.0, double _y = 0.0) 
	{ 
		x = _x; 
		y = _y; 
	}
	CDPoint(const CDPoint& other)
	{
		x = other.x;
		y = other.y;
	}
	CDPoint(const DBPOINT& other)
	{
		x = other.x;
		y = other.y;
	}
	CDPoint(const POINT& other)
	{
		FromPOINT(other);
	}
	
	// converter
	// operator POINT() const; // not allowed -> use ToPOINT
	POINT ToPOINT() const
	{
		POINT point;
		point.x	= static_cast<LONG>(x + 0.5);
		point.y	= static_cast<LONG>(y + 0.5);
		return point;
	}

	void FromPOINT(const POINT& other)
	{
		x = static_cast<double>(other.x);
		y = static_cast<double>(other.y);
	}

	// assignment operator
	CDPoint& operator=(const CDPoint& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	// arithmetic operator
	CDPoint operator+(const CDPoint& pt) const
	{
		return CDPoint(x + pt.x, y + pt.y);
	}
	CDPoint operator-(const CDPoint& pt) const
	{
		return CDPoint(x - pt.x, y - pt.y);
	}
	CDPoint operator*(double d) const
	{
		return CDPoint(x * d, y * d);
	}
	CDPoint operator/(double d) const
	{
		return CDPoint(x / d, y / d);
	}
	CDPoint operator-() const
	{
		return CDPoint(-x, -y);
	}

	// compound assignment operator
	CDPoint& operator+=(const CDPoint& pt)
	{
		x += pt.x;
		y += pt.y;
		return *this;
	}
	CDPoint& operator-=(const CDPoint& pt)
	{
		x -= pt.x; 
		y -= pt.y;
		return *this;
	}
	CDPoint& operator*=(double d)
	{
		x *= d;
		x *= d;
		return *this;
	}
	CDPoint& operator/=(double d)
	{
		x /= d; 
		y /= d;
		return *this;
	}

	// relational operator
	bool operator==(const CDPoint& other) const
	{
		return other.x == x && other.y == y;
	}
	bool operator!=(const CDPoint& other) const
	{
		return other.x != x || other.y != y;
	}
	bool operator>(const CDPoint& other) const
	{
		return x > other.x && y > other.y;
	}
	bool operator>=(const CDPoint& other) const
	{
		return x >= other.x && y >= other.y;
	}
	bool operator<(const CDPoint& other) const
	{
		return x < other.x && y < other.y;
	}
	bool operator<=(const CDPoint& other) const
	{
		return x <= other.x && y <= other.y;
	}
};
inline CDPoint operator*(double d, const CDPoint& pt)
{
	return pt * d;
}


struct DBRECT
{
	double left;
	double top;
	double right;
	double bottom;
};

class CDRect : public DBRECT
{
public:
	// constructor
	CDRect(double l = 0.0, double t = 0.0, double r = 0.0, double b = 0.0) 
	{
		left   = l; 
		top    = t; 
		right  = r; 
		bottom = b; 
	}	
	CDRect(const CDRect& other)
	{
		left = other.left;
		top = other.top;
		right = other.right;
		bottom = other.bottom;
	}
	CDRect(const DBRECT& other)
	{
		left	= other.left;
		top		= other.top;
		right	= other.right;
		bottom	= other.bottom;
	}
	CDRect(const RECT& other)
	{
		FromRECT(other);
	}

	// converter
	RECT ToRECT() const
	{
		RECT rect;
		rect.left	= (long)(left+.5);
		rect.top	= (long)(top+.5);
		rect.right	= (long)(right+.5);
		rect.bottom = (long)(bottom+.5);
		return rect;	
	}
	void FromRECT(const RECT& other)
	{
		left   = static_cast<double>(other.left);
		top    = static_cast<double>(other.top);
		right  = static_cast<double>(other.right);
		bottom = static_cast<double>(other.bottom);
	}

	// assignment operator
	CDRect& operator=(const CDRect& other)
	{
		left   = other.left;
		top    = other.top;
		right  = other.right;
		bottom = other.bottom;
		return *this;
	}

	// relational operator
	bool operator==(const CDRect& other) const
	{
		return left == other.left && top == other.top && right == other.right && bottom == other.bottom;
	}
	bool operator!=(const CDRect& other) const
	{
		return left != other.left || top != other.top || right != other.right || bottom != other.bottom;
	}

	// utility
	double Width() const  
	{
		return fabs(right - left);
	}
	double Height() const 
	{
		return fabs(bottom - top); 
	}
	CDPoint CenterPoint() const 
	{
		return CDPoint((left + right) / 2.0, (top + bottom) / 2.0); 
	}

	bool IsEmpty() const 
	{
		return Width() <= 0.0 || Height() <= 0.0;
	}

	void SetRectEmpty() 
	{
		left = right = top = bottom = 0.0;
	}

	BOOL PtInRect( const CDPoint& point ) const
	{
		if ( left > point.x || right <= point.x ) return FALSE;
		if ( top > point.y || bottom <= point.y ) return FALSE;
	
		return TRUE;
	}

	void OffsetRect(DBPOINT point)
	{
		OffsetRect(point.x, point.y);
	}
	void OffsetRect( double x, double y )
	{
		left += x;
		top += y;
		right += x;
		bottom += y;
	}

	void DeflateRect(double l, double t, double r, double b) 
	{
		left+=l; top+=t; right-=r; bottom-=b; 
	}
	void InflateRect(double l, double t, double r, double b) 
	{
		left-=l; top-=t; right+=r; bottom+=b; 
	}

	void IntersectRect( const CDRect& rc1, const CDRect& rc2 ) 
	{
		BOOL bIntersect =  (		rc2.left < rc1.right
								&&	rc2.right > rc1.left
								&&	rc2.top < rc1.bottom
								&&	rc2.bottom > rc1.top
							); 

		if ( bIntersect )
		{
			left	= max(rc1.left, rc2.left);
			top		= max(rc1.top, rc2.top);
			right	= min(rc1.right, rc2.right);
			bottom	= min(rc1.bottom, rc2.bottom);
		}
		else
		{
			left = top = right = bottom = 0.0;
		}
	}

	void UnionRect( const CDRect& rc1, const CDRect& rc2 ) 
	{
		left	= min(rc1.left, rc2.left);
		right	= max(rc1.right, rc2.right);
		top		= min(rc1.top, rc2.top);
		bottom	= max(rc1.bottom, rc2.bottom);
	}

	void NormalizeRect()
	{
		double t;
		if ( left > right ) { t = left; left = right ; right = t; }
		if ( top > bottom ) { t = top; top = bottom; bottom = t; }
	}

	BOOL IsOverlap( const CDRect& OtherRect ) const
	{
		if ( left > OtherRect.left ) {	if ( left > OtherRect.right ) return FALSE; }
		else { if ( right < OtherRect.left ) return FALSE;	}
		
		if ( top > OtherRect.top )	{ if ( top > OtherRect.bottom ) return FALSE; }
		else { if ( bottom < OtherRect.top ) return FALSE; }
		
		return TRUE;
	}
	
	BOOL IsContain(const CDRect& OtherRect) const
	{
		return left <= OtherRect.left && right >= OtherRect.right && top <= OtherRect.top && bottom >= OtherRect.bottom;
	}
	
	BOOL IsOverlapWithLine(const CDPoint& pt1, const CDPoint& pt2) const
	{
		CDRect TempRect;

		if ( pt1.x < pt2.x ) { TempRect.left = pt1.x; TempRect.right = pt2.x; }
		else { TempRect.left = pt2.x; TempRect.right = pt1.x; }

		if ( pt1.y < pt2.y ) { TempRect.top = pt1.y; TempRect.bottom = pt2.y; }
		else { TempRect.top = pt2.y; TempRect.bottom = pt1.y; }
		
		if ( left>TempRect.right || right<TempRect.left || top>TempRect.bottom || bottom<TempRect.top )
		{
			return FALSE;
		}
		
		double dDx = pt1.x - pt2.x;
		double dDy = pt1.y - pt2.y;
		
		double dP1 = dDy * ( left - pt2.x )	- dDx * (top - pt2.y );
		double dP2 = dDy * ( left - pt2.x )	- dDx * (bottom - pt2.y );
		double dP3 = dDy * ( right - pt2.x ) - dDx * (top - pt2.y );
		double dP4 = dDy * ( right - pt2.x ) - dDx * (bottom - pt2.y );
		
		if ( dP1 > 0.0f ) { if ( dP2>0.0f && dP3>0.0f && dP4>0.0f ) return FALSE; }
		else if ( dP1 < 0.0f ) { if ( dP2<0.0f && dP3<0.0f && dP4<0.0f ) return FALSE; }
		
		return TRUE;
	}
};

class CRectEx
{
public:
	int left, top, right, bottom;

	CRectEx() : left(0), top(0), right(0), bottom(0) {}
	CRectEx(int left, int top, int right, int bottom) : left(left), top(top), right(right), bottom(bottom) {}

	int Width() const 
	{
		return right - left + 1;
	}
	int Height() const 
	{
		return bottom - top + 1;
	}
	POINT CenterPoint() const
	{
		POINT center;
		center.x = (left + right) / 2;
		center.y = (top + bottom) / 2;

		return center;
	}
	RECT ToRECT() const
	{
		RECT rect;
		rect.left = static_cast<LONG>(left);
		rect.top = static_cast<LONG>(top);
		rect.right = static_cast<LONG>(right);
		rect.bottom = static_cast<LONG>(bottom);

		return rect;
	}

	void SetRect(int left, int top, int right, int bottom)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}
	void SetRectCentered(int centerx, int centery, int width, int height)
	{
		left = centerx - (width / 2);
		top = centery - (height / 2);
		right = left + width - 1;
		bottom = top + height - 1;
	}

	bool PointInRect(int x, int y) const
	{
		return x >= left && x <= right && y >= top && y <= bottom;
	}
};

#endif //__DATA_TYPES_H__