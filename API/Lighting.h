#ifndef __LIGHTING_H__
#define __LIGHTING_H__

#include <cassert>
#include <GL/glut.h>
#include "Pos.h"

struct Lighting
{
    PosXYZ Center;
    float underpass;	// How much lower the light
			// is displayed under the center
    
    Lighting(): Center(0,0,0), underpass(0.1) { }
    
    void setCenter(PosXYZ P)
    {
	Center.X = P.X;
	Center.Y = P.Y;
	Center.Z = P.Z;
    }
    
    void setMode(int i = 0)
    {
	if(i == 0)
	{
	// glClear(GL_COLOR_BUFFER_BIT);
	float Top[4] = { 0.0, 0.0, 1.0, 0.0 };
	float Bottom[4] = { 0.0, 0.0, -1.0, 0.0 };
	float ambientPower[4] = { 0.0, 0.0, 0.0, 1.0 };
	
	float diffusePower[4] = { 0.8, 0.8, 0.8, 1.0 };
	float specularPower[4] = { 0.8, 0.8, 0.8, 1.0 };
	
	glLightfv(GL_LIGHT0, GL_POSITION, Top);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientPower);
	
	glLightfv(GL_LIGHT1, GL_POSITION, Bottom);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientPower);
	
	float LightDir[4] = { Center.X , Center.Y , 0.5 , 1.0 };
	// float LightPos[4] = { 0.0, 0.0, 0.5, 1.0 };
	
	glLightfv(GL_LIGHT2, GL_POSITION, LightDir);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularPower);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffusePower);
	
	glEnable(GL_LIGHTING);
	glShadeModel( GL_SMOOTH );
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	// glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
	glEnable( GL_DEPTH_TEST );
	}
	else if(i==1)
	{
		// .. Create your own lighting setting here .. 
	}
    }
    
    void toggleTransparency(bool On)
    {
	if(On)
	{
	    glEnable( GL_BLEND );
	    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}
	else
	{
	    glDisable( GL_BLEND );
	}
    }
    
};
#endif