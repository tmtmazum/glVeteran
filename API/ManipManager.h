#ifndef MANIP_MANAGER_H
#define MANIP_MANAGER_H

#include <vector>
#include <map>
#include "GEOMETRY.h"
#include "Pos.h"
#include "DRAW.h"

/*
struct Manip
{
    WO* owner;
};

struct LineManip : public Manip
{
    float* value;
    PosXYZ pos; 		int orientation;  // x,y,z: 0,1,2
    enum state_enum
    {
	HIDDEN,
	VISIBLE,
	OVER
    };
    
    int state;
    LineManip() {}
    LineManip( float* v , PosXYZ p , int ori ):
	value(v), pos(p), orientation(ori) { state = VISIBLE; }
};


struct ManipManager
{
    typedef std::map< int, WO* > ListWO;
    std::map< int, WO* > scene_objects;
    // std::map< int , std::map< int , Manip* > > Manips;
    LineManip* l;
    int getNumObjects()
    {
	return scene_objects.size();
    }
    
    void add( WO* obj )
    {
	VecF npScale = (obj->get( WO::NP_SCALE ));
// LineManip* l1 = new LineManip( &npScale.at(0) , npScale.at(1)*0.6 , npScale.at(2)*0.6 );
// 	l = l1;
    
	// ListWO.insert( std::pair< int, WO* >( 0 , obj ) );
    }
    
    void draw()
    {
	for(ListWO::iterator it = scene_objects.begin(); it != scene_objects.end(); it++)
	{
	    setTransforms3D( it->second );
		draw3D_pure( it->second );
		draw3D_pure( *l );
	    resetTransforms3D( it->second );
	}
    }
};
*/
#endif
