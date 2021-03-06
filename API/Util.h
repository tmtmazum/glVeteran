#ifndef __UTIL_H__
#define __UTIL_H__

#include <cmath>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>

#include <limits>
#include <GL/glut.h>

#define END_F std::numeric_limits<float>::max()
#define END_I std::numeric_limits<int>::max()

typedef std::vector<float> VecF;
typedef std::vector<std::string> VecS;
typedef std::map<std::string, float> MapSF;
typedef std::map<int,float> MapIF;
typedef std::vector<std::string> VecS;
typedef std::string Str;

namespace Util
{
    
    inline float root_sum_of_squares( float t1, float t2, float t3 )
    {
	return std::sqrt( std::pow(t1, 2) + std::pow(t2, 2) + std::pow(t3, 2) );
    }
    
    inline float min(float f1, float f2)
    {
	return f1 < f2 ? f1 : f2;
    }
    inline float max(float f1, float f2)
    {
	return f1 < f2 ? f2 : f1;
    }
    
    inline float min(float f1, float f2, float f3, float f4)
    {
	return min( min( min(f1,f2), f3) , f4 ); 
    }
    
    inline float stringToFloat( std::string s )
    {
	return ::atof( s.c_str() );
    }
    
    inline std::string floatToString( float f )
    {
	std::ostringstream ss;
	ss << f;
	std::string s(ss.str());
	return s;
    }

    inline void moderateDivEq(float* target, float rate, float snapToZeroRange = 0.00001)
    {
	// Example Use:
	// moderateDivEq( &mouseDiff.X , 0.007 );
	*target = ( *target / (1+rate) );
	*target = (*target < snapToZeroRange && *target > -snapToZeroRange ? 0 : *target);
    }
    
    inline void printToScreen( std::string text , PosXYZ p )
    {
	glRasterPos3f( p.X , p.Y , p.Z );
	for(std::string::iterator i = text.begin(); i != text.end(); ++i)
	    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *i);
    }

};

struct bitmask
{
    int value;
    bitmask(int i)
    {
	value = i;
    }
    
    void set(int i , bool b)
    {
	i = pow(2,i);
	if(b)
	    value = value | i;
	else
	    value = value & ~i;
    }
    
    bool get(int i)
    {
	i = pow(2,i);
	return value & i;
    }
};

#endif