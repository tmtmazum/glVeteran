
#include "DRAW.h"

void draw2D( WO& obj )
{
    assert( obj.has(WO::GEOMETRY) && obj.has(WO::POSITION) );
    bool hasRot = obj.has(WO::ROTATION);
    bool hasColor = obj.has(WO::COLOR);
    bool hasAlpha = obj.has(WO::ALPHA);
    bool hasScale = obj.has(WO::SCALE);
    
    if(hasColor && hasAlpha)
    {
	VecF C = obj.get(WO::COLOR);
	VecF A = obj.get(WO::ALPHA);
	glColor4f( C.at(0) , C.at(1) , C.at(2) , A.at(0) );
    }
    else if(hasColor)
    {
	VecF C = obj.get(WO::COLOR);
	glColor4f( C.at(0) , C.at(1) , C.at(2) , 1.0 );
    }
    int t = obj.getGeometryType();
    switch( t )
    {
	case GO::RECT:
	{
	    VecF P = obj.get(WO::POSITION);
	    VecF V = obj.getGeometryData();
	    PosXY Pt( P.at(0) , P.at(1) );
	    PosXY Pt2( P.at(0) + V.at(0) , P.at(1) );
	    PosXY Pt3( P.at(0) + V.at(0) , P.at(1) + V.at(1) );
	    PosXY Pt4( P.at(0) , P.at(1) + V.at(1) );
	    if( hasRot )
	    {
		VecF Rot = obj.get(WO::ROTATION);
		float angl = Rot.at(0) * PI;
		Pt2 = transform::rotateXY( Pt2 , Pt , angl , false );
		Pt3 = transform::rotateXY( Pt3 , Pt , angl , false );
		Pt4 = transform::rotateXY( Pt4 , Pt , angl , false );
	    }
	    glBegin( GL_QUADS );
		Pt.getVertex();
		Pt2.getVertex();
		Pt3.getVertex();
		Pt4.getVertex();
	    glEnd();
	}
	    break;
	case GO::LINE:
	{
	    VecF P = obj.get(WO::POSITION);
	    VecF V = obj.getGeometryData();
	    PosXY Pt( P.at(0) , P.at(1) );
	    PosXY Pt2( V.at(0) , V.at(1) );
	    if( hasRot )
	    {
		VecF Rot = obj.get(WO::ROTATION);
		float angl = Rot.at(0) * PI;
		Pt2 = transform::rotateXY( Pt2 , Pt , angl , false );
	    }
	    glBegin( GL_LINES );
		Pt.getVertex();
		Pt2.getVertex();
	    glEnd();
	}/*
	case GO::STAR:
	{
	    VecF P = obj.get(WO::POSITION);
	    float size = 0.01;
	    glBegin( GL_LINES );
		glVertex2f( 
	    glEnd();
	}*/
    }
}

void setTransforms3D( WO& obj )
{
    VecF rotation, npScale, scale, pos , color , alpha;
    
    if( obj.has( WO::POSITION ) )
    {
	pos = obj.get( WO::POSITION );
	glTranslatef( pos.at(0) , pos.at(1) , pos.at(2) );
    }
    if( obj.has( WO::NP_SCALE ) )
    {
	npScale = obj.get( WO::NP_SCALE );
	glScalef( npScale.at(0) , npScale.at(1) , npScale.at(2) );
    }
    if( obj.has( WO::SCALE ) )
    {
	scale = obj.get( WO::SCALE );
	glScalef( scale.at(0) , scale.at(0) , scale.at(0) );
    }
    if( obj.has( WO::ROTATION ) )
    {
	rotation = obj.get( WO::ROTATION );
	glRotatef( rotation.at(0) , 0.0 , 0.0 , 1.0f );
	glRotatef( rotation.at(1) , 0.0 , 1.0 , 0.0f );
    }
    float currColor[4];
    if( obj.has( WO::COLOR ) )
    {
	glGetFloatv( GL_CURRENT_COLOR , currColor );
	color = obj.get( WO::COLOR );
	if( obj.has( WO::ALPHA ) )
	    glColor4f( color.at(0) , color.at(1) , color.at(2) , obj.get( WO::ALPHA ).at(0) );
	else
	    glColor3fv( &color.at(0) );
	    //glColor3f( color.at(0) , color.at(1) , color.at(2) );
    }
}

void resetTransforms3D( WO& obj )
{   
    VecF rotation, npScale, scale, pos , color , alpha;
    
    /*
    if( obj.has( WO::COLOR ) )
    {
	glColor4fv( currColor );
    }*/
    if( obj.has( WO::ROTATION ) )
    {
	rotation = obj.get( WO::ROTATION );
	glRotatef( -rotation.at(0) , 0.0 , 0.0 , 1.0f );
	glRotatef( -rotation.at(1) , 0.0 , 1.0 , 0.0f );
    }
    if( obj.has( WO::SCALE ) )
    {
	scale = obj.get( WO::SCALE );
	glScalef( 1/scale.at(0) , 1/scale.at(0) , 1/scale.at(0) );
    }
    if( obj.has( WO::NP_SCALE ) )
    {
	npScale = obj.get( WO::NP_SCALE );
	glScalef( 1/npScale.at(0) , 1/npScale.at(1) , 1/npScale.at(2) );
    }
    if( obj.has( WO::POSITION ) )
    {
	pos = obj.get( WO::POSITION );
	glTranslatef( pos.at(0) , pos.at(1) , pos.at(2) );
    }
}


/*
inline void draw3D_pure( LineManip& LM )
{
    static int count = 0;
    float alpha = 0.5;
    if( LM.state == LineManip::HIDDEN )
	return;
    else if( LM.state == LineManip::OVER )
    {
	alpha = 1.0;
    }
    else alpha = 0.5;
    //else glLineWidth( 1.0 );
    
    float x_add, y_add, z_add;
    glColor4f( 1.0 , 1.0 , 1.0 , alpha );
    if( LM.orientation == 0 )
    {
	x_add = 0.5;
	y_add = 0.02;
	z_add = 0.02;
    glBegin( GL_LINES );
	glVertex3f( LM.pos.X -x_add , LM.pos.Y , LM.pos.Z );
	glVertex3f( LM.pos.X +x_add , LM.pos.Y , LM.pos.Z );
	
	glVertex3f( LM.pos.X -x_add , LM.pos.Y-y_add , LM.pos.Z );
	glVertex3f( LM.pos.X -x_add , LM.pos.Y+y_add , LM.pos.Z );
	glVertex3f( LM.pos.X +x_add , LM.pos.Y-y_add , LM.pos.Z );
	glVertex3f( LM.pos.X +x_add , LM.pos.Y+y_add , LM.pos.Z );
	glVertex3f( LM.pos.X +x_add , LM.pos.Y , LM.pos.Z-z_add );
	glVertex3f( LM.pos.X +x_add , LM.pos.Y , LM.pos.Z+z_add );
	glVertex3f( LM.pos.X -x_add , LM.pos.Y , LM.pos.Z-z_add );
	glVertex3f( LM.pos.X -x_add , LM.pos.Y , LM.pos.Z+z_add );
    glEnd();
    }
    else if( LM.orientation == 1 )
    {
	y_add = 0.5;
	x_add = 0.01;
	z_add = 0.01;
    glBegin( GL_LINES );
	glVertex3f( LM.pos.X , LM.pos.Y-y_add , LM.pos.Z );
	glVertex3f( LM.pos.X , LM.pos.Y+y_add , LM.pos.Z );
	
	glVertex3f( LM.pos.X-x_add , LM.pos.Y-y_add , LM.pos.Z );
	glVertex3f( LM.pos.X+x_add , LM.pos.Y-y_add , LM.pos.Z );
	glVertex3f( LM.pos.X-x_add , LM.pos.Y+y_add , LM.pos.Z );
	glVertex3f( LM.pos.X+x_add , LM.pos.Y+y_add , LM.pos.Z );
	glVertex3f( LM.pos.X , LM.pos.Y-y_add , LM.pos.Z-z_add );
	glVertex3f( LM.pos.X , LM.pos.Y-y_add , LM.pos.Z+z_add );
	glVertex3f( LM.pos.X , LM.pos.Y+y_add , LM.pos.Z-z_add );
	glVertex3f( LM.pos.X , LM.pos.Y+y_add , LM.pos.Z+z_add );
    glEnd();
    }
    else if( LM.orientation == 2 )
    {
	z_add = 0.5;
	x_add = 0.01;
	z_add = 0.01;
    glBegin( GL_LINES );
	glVertex3f( LM.pos.X , LM.pos.Y , LM.pos.Z-z_add );
	glVertex3f( LM.pos.X , LM.pos.Y , LM.pos.Z+z_add );
	glVertex3f( LM.pos.X-x_add , LM.pos.Y , LM.pos.Z-z_add );
	glVertex3f( LM.pos.X+x_add , LM.pos.Y , LM.pos.Z-z_add );
	glVertex3f( LM.pos.X-x_add , LM.pos.Y , LM.pos.Z+z_add );
	glVertex3f( LM.pos.X+x_add , LM.pos.Y , LM.pos.Z+z_add );
	glVertex3f( LM.pos.X , LM.pos.Y-y_add , LM.pos.Z-z_add );
	glVertex3f( LM.pos.X, LM.pos.Y+y_add , LM.pos.Z-z_add );
	glVertex3f( LM.pos.X , LM.pos.Y-y_add , LM.pos.Z+z_add );
	glVertex3f( LM.pos.X, LM.pos.Y+y_add , LM.pos.Z+z_add );
	
    glEnd();
    }
    else assert( false );
    
    count++;
}
*/

void draw3D( WO& obj )
{
    VecF rotation, npScale, scale, pos , color , alpha;
    
    float currColor[4];
    
    if( obj.has( WO::POSITION ) )
    {
	pos = obj.get( WO::POSITION );
	glTranslatef( pos.at(0) , pos.at(1) , pos.at(2) );
    }
    if( obj.has( WO::NP_SCALE ) )
    {
	npScale = obj.get( WO::NP_SCALE );
	glScalef( npScale.at(0) , npScale.at(1) , npScale.at(2) );
    }
    if( obj.has( WO::SCALE ) )
    { 
	scale = obj.get( WO::SCALE );
	glScalef( scale.at(0) , scale.at(0) , scale.at(0) );
    }
    if( obj.has( WO::ROTATION ) )
    {
	rotation = obj.get( WO::ROTATION );
	glRotatef( rotation.at(0) , 0.0 , 0.0 , 1.0f );
	glRotatef( rotation.at(1) , 0.0 , 1.0 , 0.0f );
    }
    if( obj.has( WO::COLOR ) )
    {
	glGetFloatv( GL_CURRENT_COLOR , currColor );
	color = obj.get( WO::COLOR );
	if( obj.has( WO::ALPHA ) )
	    glColor4f( color.at(0) , color.at(1) , color.at(2) , obj.get( WO::ALPHA ).at(0) );
	else
	    glColor3fv( &color.at(0) );
	    //glColor3f( color.at(0) , color.at(1) , color.at(2) );
    }
    draw3D_pure( obj );
    
    if( obj.has( WO::COLOR ) )
    {
	glColor4fv( currColor );
    }
    if( obj.has( WO::ROTATION ) )
    {
	glRotatef( -rotation.at(0) , 0.0 , 0.0 , 1.0f );
	glRotatef( -rotation.at(1) , 0.0 , 1.0 , 0.0f );
    }
    if( obj.has( WO::SCALE ) )
    {
	glScalef( 1/scale.at(0) , 1/scale.at(0) , 1/scale.at(0) );
    }
    if( obj.has( WO::NP_SCALE ) )
    {
	glScalef( 1/npScale.at(0) , 1/npScale.at(1) , 1/npScale.at(2) );
    }
    if( obj.has( WO::POSITION ) )
    {
	glTranslatef( -pos.at(0) , -pos.at(1) , -pos.at(2) );
    }
}

void draw3D_pure( WO& obj , bool diagnostic_shade )
// draws the object without any transformations
{
   int t = obj.getGeometryType();
    PosXY tile(1.0 , 1.0); bool textr_on = false;
    if( obj.has( WO::TILING_FACTOR ) )
    {
	    VecF t = obj.get( WO::TILING_FACTOR );
	    tile.X = t.at(0);
	    tile.Y = t.at(1);
	    textr_on = true;
    }
   switch( t )
   {
       case GO::STAR:
       {
	   float r = 0.005;
	   glBegin( GL_LINES );
		glVertex3f( -r , 0, 0 );
		glVertex3f( r , 0, 0 );
		glVertex3f( 0 , -r, 0 );
		glVertex3f( 0 , r, 0 );
		glVertex3f( 0 , 0, -r );
		glVertex3f( 0 , 0, r );
	    glEnd();
	   break;
       }
       case GO::LIGHT_RADIAL:
       {
	   VecF num = obj.getGeometryData();
	   assert( !num.empty() && obj.has(WO::POSITION) && obj.has(WO::COLOR));
	   int LIGHT_ID = GL_LIGHT0; //num.at(0);
	   float LIGHT_ATTENUATION = (num.size() > 1 ? num.at(1) : 1.0);
	   if( LIGHT_ATTENUATION < 0 ) LIGHT_ATTENUATION = 0;
	   LIGHT_ATTENUATION = 1/LIGHT_ATTENUATION;
	   
	   VecF Pos = obj.get( WO::POSITION );
	   float pos[4] = { 0.0 , 0.0 , 0.0 , 1.0 };
	   glLightfv(LIGHT_ID, GL_POSITION, pos );
	   glLightf(LIGHT_ID, GL_CONSTANT_ATTENUATION, 0.0*LIGHT_ATTENUATION);
	   glLightf(LIGHT_ID, GL_QUADRATIC_ATTENUATION, 10.0*LIGHT_ATTENUATION);

	    glLightfv(LIGHT_ID, GL_SPECULAR, &obj.get(WO::COLOR).front() );
	    glLightfv(LIGHT_ID, GL_DIFFUSE, &obj.get(WO::COLOR).front() );
	    glLightfv(LIGHT_ID, GL_AMBIENT, &obj.get(WO::COLOR).front());
	    
	    glEnable( GL_LIGHTING );
	    // glDisable( LIGHT_ID );
	    glEnable( LIGHT_ID );
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);
	glShadeModel( GL_SMOOTH );
	
	if(diagnostic_shade)
	{
	    WO light_marker;
	    light_marker.setGeometry( GO::STAR , END_F );
	    light_marker.set( WO::COLOR , Colors::Yellow.R , Colors::Yellow.G ,
			      Colors::Yellow.B , END_F );
	    draw3D( light_marker );
	}
	   break;
       }
       case GO::LINE:
       {
	    VecF pt = obj.getGeometryData();
	    assert( pt.size() >= 3 );
	    PosXYZ point( pt.at(0) , pt.at(1) , pt.at(2) );
	    glBegin( GL_LINES );
		glVertex3f(0,0,0);
		point.getVertex();
	    glEnd();
	    break;
       }
       case GO::FACE:
	   {
	   VecF P = obj.get( WO::POSITION );
	   PosXYZ pos(0,0,0);
	   glBegin( GL_QUAD_STRIP );
	    if(textr_on) glTexCoord2f( 0 , tile.Y );
	    glVertex3f( pos.X - 0.5 , pos.Y , pos.Z + 0.5 );
	    if(textr_on) glTexCoord2f( tile.X , tile.Y );
	    glVertex3f( pos.X + 0.5 , pos.Y , pos.Z + 0.5 );
	    if(textr_on) glTexCoord2f( 0 , 0 );
	    glVertex3f( pos.X - 0.5 , pos.Y , pos.Z - 0.5 );
	    if(textr_on) glTexCoord2f( tile.X , 0 );
	    glVertex3f( pos.X + 0.5 , pos.Y , pos.Z - 0.5 );
	   glEnd();
	   }
	   break;
       case GO::FACE_BOTTOM:
	   {
	   VecF P = obj.get( WO::POSITION );
	   PosXYZ pos(0,0,0);
	   // PosXYZ pos( P.at(0) , P.at(1) , P.at(2) );
	   glBegin( GL_QUAD_STRIP );
	    if(textr_on) glTexCoord2f( 0 , tile.Y );
	    glVertex3f( pos.X - 0.5 , pos.Y + 0.5 , pos.Z );
	    if(textr_on) glTexCoord2f( tile.X , tile.Y );
	    glVertex3f( pos.X + 0.5 , pos.Y + 0.5 , pos.Z );
	    if(textr_on) glTexCoord2f( 0 , 0 );
	    glVertex3f( pos.X - 0.5 , pos.Y - 0.5 , pos.Z );
	    if(textr_on) glTexCoord2f( tile.X , 0 );
	    glVertex3f( pos.X + 0.5 , pos.Y - 0.5 , pos.Z );
	   glEnd();
	   }
	   break;
       case GO::V_WALL:
       {
	   VecF D = obj.getGeometryData();
	   float height = D.at(0); int i = 1;
	   
	   while(true)
	   {
	       if( i + 5 >= D.size() ) { DEBUG("ERROR OCCURRED w/ i=",i); break; }
		PosXYZ current = PosXYZ( D.at(i) , D.at(i+1) , D.at(i+2) );
		PosXYZ next = PosXYZ( D.at(i + 3) , D.at(i+4) , D.at(i+5) );
		
		glBegin( GL_TRIANGLE_STRIP );
		    if(textr_on) glTexCoord2f( 0 , tile.Y );
		    glVertex3f( current.X , current.Y , current.Z );
		    if(textr_on) glTexCoord2f( tile.X , tile.Y );
		    glVertex3f( next.X , next.Y , next.Z );
		    if(textr_on) glTexCoord2f( 0 , 0 );
		    glVertex3f( current.X , current.Y , current.Z + height );
		    if(textr_on) glTexCoord2f( tile.X , 0 );
		    glVertex3f( next.X , next.Y , next.Z + height );
		glEnd();
		
		if( (i+6) >= D.size() )
		    break;
		i += 3;
	   }
       }
       break;
       case GO::GRID_CHEQUERED:
       {
	    float interval = 0.1;
	    float zUnder = 0.0001;
	    
	    ColorRGBA Black( 0.0, 0.0, 0.0, 0.95 );
	    ColorRGBA White( 1.0, 1.0, 1.0, 0.95 );
	    
	    bool alternate = false;
	    
	    for(float i = -1.0; i < (1.0 - interval); i += interval)
	    {
		if( alternate ) Black.get();
		else White.get();
		
		for(float j = -1.0; j < (1.0 - interval); j += interval)
		{   
		    glBegin( GL_POLYGON );
		    if( alternate ) Black.get();
		    else White.get();
			glVertex3f( i , j , zUnder );
			glVertex3f( i+interval , j , zUnder );
			glVertex3f( i+interval , j+interval , zUnder );
			glVertex3f( i , j+interval , zUnder );
		    glEnd();
		    
		    alternate = !alternate;
		}
	    }
	   break;
       }
       case GO::CUBE:
	{
	   VecF P = obj.get( WO::POSITION );
	   PosXYZ pos(0,0,0);
	   // PosXYZ pos( P.at(0) , P.at(1) , P.at(2) );
	    if( diagnostic_shade )
		Colors::Red.get();
	   glBegin( GL_TRIANGLE_STRIP );
	    glVertex3f( pos.X - 0.5 , pos.Y - 0.5 , pos.Z - 0.5 );
	    glVertex3f( pos.X - 0.5 , pos.Y - 0.5 , pos.Z + 0.5 );
	    glVertex3f( pos.X + 0.5 , pos.Y - 0.5 , pos.Z - 0.5 );
	    if( diagnostic_shade) Colors::Orange.get();
	    glVertex3f( pos.X + 0.5 , pos.Y - 0.5 , pos.Z + 0.5 );
	    
	    glVertex3f( pos.X + 0.5 , pos.Y + 0.5 , pos.Z - 0.5 );
	    if( diagnostic_shade) Colors::Yellow.get();
	    glVertex3f( pos.X + 0.5 , pos.Y + 0.5 , pos.Z + 0.5 );
	    
	    glVertex3f( pos.X - 0.5 , pos.Y + 0.5 , pos.Z - 0.5 );
	    if( diagnostic_shade) Colors::DarkOrange.get();
	    glVertex3f( pos.X - 0.5 , pos.Y + 0.5 , pos.Z + 0.5 );
	    
	    glVertex3f( pos.X - 0.5 , pos.Y - 0.5 , pos.Z - 0.5 );
	    if( diagnostic_shade) Colors::Red.get();
	    glVertex3f( pos.X - 0.5 , pos.Y - 0.5 , pos.Z + 0.5 );
	   glEnd();
	   
	   if( diagnostic_shade )
	       Colors::Green.get();
	   glBegin( GL_TRIANGLE_STRIP );
	    glVertex3f( pos.X - 0.5 , pos.Y - 0.5 , pos.Z + 0.5 );
	    glVertex3f( pos.X + 0.5 , pos.Y - 0.5 , pos.Z + 0.5 );
	    glVertex3f( pos.X - 0.5 , pos.Y + 0.5 , pos.Z + 0.5 );
	    glVertex3f( pos.X + 0.5 , pos.Y + 0.5 , pos.Z + 0.5 );
	   glEnd();
	   
	   if( diagnostic_shade )
	       Colors::Blue.get();
	   glBegin( GL_TRIANGLE_STRIP );
	    glVertex3f( pos.X - 0.5 , pos.Y - 0.5 , pos.Z - 0.5 );
	    glVertex3f( pos.X + 0.5 , pos.Y - 0.5 , pos.Z - 0.5 );
	    glVertex3f( pos.X - 0.5 , pos.Y + 0.5 , pos.Z - 0.5 );
	    glVertex3f( pos.X + 0.5 , pos.Y + 0.5 , pos.Z - 0.5 );
	   glEnd();
	   break;
	}
       case GO::CYLINDER:
       {
	   assert( !obj.getGeometryData().empty() );
	   int splits = obj.getGeometryData().at(0);
	   float radius = 1;
	   float height = 1;
	   
	   PosRP st( radius , 0.0 );
	   float V[ 2*(splits + 1) ][ 3];
	   float T[ 2*(splits + 1) ][ 2];
	    for(int i = 0; i < 2*splits; ++i)
	    {
		PosXY p( st );
		PosXYZ p1( p ); p1.Z = (i % 2 == 0 ? height : -height);
		
		V[i][0] = p1.X;
		V[i][1] = p1.Y;
		V[i][2] = p1.Z;
		
		if(textr_on)
		{
		    if(i%2==0)
		    {
		    T[i][0] = tile.X * ((float)i/2)/(splits+1);
		    T[i][1] = 0;
		    }
		    else
		    {
		    T[i][0] = T[i-1][0];
		    T[i][1] = tile.Y;
		    }
		}
		
		if(i == 0 || i==1)
		{
		    V[2*splits+i][0] = p1.X;
		    V[2*splits+i][1] = p1.Y;
		    V[2*splits+i][2] = p1.Z;
		    
		    T[2*splits+i][0] = tile.X * ((2*(float)splits+i)/2) / (splits+1);
		    T[2*splits+i][1] = tile.Y * i;
		}
		
		if(i % 2 == 1 ) st.angle = st.angle.value + 2*PI/splits;
	    }
	    
	    
	    if( true /*GC.enabledFaces & GO_CYLINDER::SIDES*/ )
	    {
		glBegin( GL_QUAD_STRIP );
		    for(int i = 0; i < 2*(splits+1); ++i)
		    {
			if(textr_on)
			{
			    glTexCoord2f( T[i][0] , T[i][1] );
			    /*
			    if(i==0)
				glTexCoord2f( 0.0 , 0.0 );
			    else if(i==1)
				glTexCoord2f( 0.0 , tile.Y );
			    else if(i+2 == 2*(splits+1))
				glTexCoord2f( tile.X , 0.0 );
			    else if(i+1 == 2*(splits+1))
				glTexCoord2f( tile.X , tile.Y );
			    */
			}
			glVertex3f( V[i][0] , V[i][1] , V[i][2] );

		    }
		glEnd();
		/*
		int drawType1 = GL_QUAD_STRIP;
		glEnableClientState( GL_VERTEX_ARRAY );
		glVertexPointer(3, GL_FLOAT, 0, V);
		glDrawArrays( drawType1 , 0 , 2*(splits + 1) );
		glDisableClientState( GL_VERTEX_ARRAY );
		*/
	    }
	    if( true /*GC.enabledFaces & GO_CYLINDER::FRONT*/ )
	    {
		int drawType = GL_TRIANGLE_FAN;
		glBegin( drawType );
		    glVertex3f( 0, 0, height );
		    for(int i = 0; i < splits+1; ++i)
			glVertex3fv( V[2*i] );
		glEnd();
	    }
	    if( true /*GC.enabledFaces & GO_CYLINDER::BACK*/ )
	    {
		int drawType = GL_TRIANGLE_FAN;
		glBegin( drawType );
		    glVertex3f( 0, 0, -height );
		    for(int i = 0; i < splits+1; ++i)
			glVertex3fv( V[2*i+1] );
		glEnd();
	    }
	   break;
       }
       case GO::SPHERE:
       {
	    VecF splits = obj.getGeometryData();
	   
	    GLUquadric *qobj = gluNewQuadric();
    
	    gluQuadricTexture(qobj,GL_TRUE); 
	    
	    gluSphere(qobj,1,splits.at(0),splits.at(1)); 

	    gluDeleteQuadric(qobj); 
	    break;
       }
       case GO::CONE:
       {
	   assert( !obj.getGeometryData().empty() );
	   int splits = obj.getGeometryData().at(0);
	   
	   float height = 1; float radius = 1;
	   PosRP rot( radius , 0.0 );
	   int n = 1 + (splits+1);
	   float V[ n ][ 3];
	   V[0][0] = 0;
	   V[0][1] = 0;
	   V[0][2] = 0.5;
	   for(int i = 1; i < n; ++i)
	   {
	       PosXY p( rot );
	       PosXYZ p1( p ); p1.Z = -0.5;
	       
		V[i][0] = p1.X;
		V[i][1] = p1.Y;
		V[i][2] = p1.Z;
		
		if(i==1)
		{
		    V[n-1][0] = p1.X;
		    V[n-1][1] = p1.Y;
		    V[n-1][2] = p1.Z;
		}
		
		rot.angle = rot.angle.value + 2*PI/splits;
	   }
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer(3, GL_FLOAT, 0, V);
	glDrawArrays( GL_TRIANGLE_FAN , 0 , n );
	
	V[0][2] = -0.5;
	glDrawArrays( GL_TRIANGLE_FAN , 0 , n );
	glDisableClientState( GL_VERTEX_ARRAY );
	
	break;   
       }
   }
}
