#ifndef DRAW_H
#define DRAW_H

#include "Pos.h"
#include "Util.h"
#include "GEOMETRY.h"
#include "Texture.h"
#include "DEBUG.h"
#include <cassert>
#include <GL/glut.h>
#include <vector>

struct TextureManager
{
    std::map< int, TextureIF* > tiles;
    int tile_count;
    
    int active;
    
    TextureManager(): tile_count(0), active(-1) {}
    
    void add( TextureIF* t , int i )
    {
	tiles.insert( std::pair<int,TextureIF*>( i , t ) );
	tile_count++;
    }
    
    void activate(int i)
    {
	std::map< int , TextureIF* >::iterator it = tiles.find( i );
	if( it == tiles.end() )
	{
	    DEBUG("ERROR: Invalid tile id: ", i);
	    return;
	}
	TextureIF* activeT = tiles[i];
	activeT->enable();
	
	active = i;
    }
    
    void deactivate()
    {
	TextureIF* activeT = tiles[active];
	activeT->disable();
	
	active = -1;
    }
};

void draw2D( WO& obj );
void draw3D_pure( WO& obj , bool diagnostic_shade = false );
void draw3D( WO& obj );

void setTransforms3D( WO& obj );

void resetTransforms3D( WO& obj );

// void draw3D_pure( LineManip& LM );

// void draw3D_pure( WO& obj , bool diagnostic_shade );
// draws the object without any transformations

#endif
