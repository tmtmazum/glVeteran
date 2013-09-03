#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Pos.h"
#include <GL/glut.h>

class Material
{public:
    
    PosXYZ Ambient;
    PosXYZ Diffuse;
    PosXYZ Specular;
    float Shininess;
    
    Material() {}
    Material(float f1, float f2, float f3, float f4, float f5,
	     float f6, float f7, float f8, float f9, float f10)
    {
	setAmbient(f1,f2,f3);
	setDiffuse(f4,f5,f6);
	setSpecular(f7,f8,f9);
	setShininess(f10);
    }
    void setAmbient(float f1, float f2, float f3)
    {
	Ambient = PosXYZ(f1,f2,f3);
    }
    void setDiffuse(float f1, float f2, float f3)
    {
	Diffuse= PosXYZ(f1,f2,f3);
    }
    void setSpecular(float f1, float f2, float f3)
    {
	Specular = PosXYZ(f1,f2,f3);
    }
    void setShininess(float f1)
    {
	Shininess = f1;
    }
    
    void get()
    {
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient.toArray() );
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse.toArray() );
	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular.toArray() );
	glMaterialf(GL_FRONT, GL_SHININESS, Shininess );
    }
};

namespace Materials
{
	static Material 
	whitePlastic(0.0,0.0,0.0,
		     0.55,0.55,0.55,
	      0.7,0.7,0.7,
	      0.25);
	
	static Material
	pearl(0.25,0.20725,0.20725,1,0.829,0.829,0.296648,0.296648,
	      0.296648, 0.088);
	
	static Material
	all(1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,0.3);
	
	static Material
	chrome(0.25,0.25,0.25,0.4,0.4,0.4,0.774597,0.774597, 0.774597, 0.6);
}

#endif