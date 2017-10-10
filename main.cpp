/* ---------------------------------------------------------------------------
** This is the main file for a 3D world.  This sets up a 3D world and
** creates car objects that are controlled by the user to interact with
** the 3D world.
**
** See Readme.txt for more information
**
** main.cpp
**
** Authors: Greg Bender
**          Michael Krauklis
** -------------------------------------------------------------------------*/
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

/* Standard Includes */
#include <windows.h>			// standard Windows app include
#include <GL/glut.h>			// include glut library
#include <gl/gl.h>              // standard OpenGL include
#include <gl/glu.h>             // OpenGL utilties
#include <gl/glaux.h>           // OpenGL auxiliary functions

/* Extra Includes for 3D world*/
#include "HiResTimer.h"       // hi resolution timer, so program wont depend on fps
#include "vector.h"           // vector math needed for velocity and acceleration
#include "font.cpp"			  // used to display text on screen
#include "display_list_loader.cpp"	// used to load model display lists

/* Class Code */
#include "car.cpp"			// represents a car object
#include "building.cpp"		// represents a building
#include "plane.cpp"		// represents a plane in a bounding box
#include "camera.cpp"		// the camera

/* Direct Input Includes */
#include<d3d8.h>
#include<d3dx8.h>
#include<dinput.h>
#include "CInput8.cpp"

/* XML and file includes */
#include "XMLImport/SAXMapHandler.hpp"
#include "XMLImport/global.hpp"
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SAXParser.hpp>

/* Create default objects */
Car *user_car = NULL;
Camera *camera = NULL;

/* Global MISC Variables */
HWND    hwnd;            // window handle
HINSTANCE g_Instance;    // windows variable
HDC g_HDC;                      // global device context
int mouseX, mouseY;			    // mouse coordinates
CHiResTimer *timer = NULL;		// timer variable
SAXMapHandler *handler = null;	// XML Sax parser handle
CFont *font = NULL;				// font variable (currently unused)
float tod=0;					// time of day, used for lighting
int xmax=0;
int zmax=0;
float frustum[6][4];		// frusum coords used for culling
float mx = 0.0f;			// mouse change variables
float my = 0.0f; 
float mz = 0.0f;

/* Display list variables */
GLint road_display_list0;
GLint road_display_list1;
GLint road_display_list2;
GLint road_display_list3;
GLint road_display_list4;
GLint road_display_list5;
GLint road_display_list6;
GLint road_display_list7;
GLint road_display_list8;
GLint road_display_list9;
GLint road_display_list10;
GLint road_display_list11;
GLint road_display_list12;
GLint road_display_list13;
GLint road_display_list14;
GLint office_building;
GLint office_building_2;
GLint nicehouse_building;
GLint coolhouse_building;
GLint glass_building_model;
GLint reliance;
GLint paper;
GLint parking;
GLint strip;
GLint blue;
GLint glassglass;
GLint realsmall;
GLuint road_texture;

/* Building Variables */
int number_of_buildings;
Building** building_holder;	// array to hold the buildings

/* Car Variables */
int number_of_cars;
Car** car_holder;	// array to hold the cars
bool** road_path;	// array to hold path for AI of cars

/* Default Lighting Variables */
float ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };     // ambient light
float diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };     // diffuse light
float lightPosition[] = { 0.0f, 0.0f, 0.0f, 0.0f };   // spotlight position

/* Function headers */
void buildWorld(SAXMapHandler *handler);
void renderWorld(SAXMapHandler *handler);

/* 
* Direct Input Initilization
* calls funtions to initilize direct input
*/
void DI_Init(void) {

  Init_CInput8(g_Instance);      
  Init_Keyboard(hwnd); 
  Init_Mouse(hwnd);
} // DI_Input

/*
* Extract Frustum, grabs the frustum coordinates and puts them in 
* the frustum array.  This function came from 
* http://www.markmorley.com/opengl/frustumculling.html
*/
void ExtractFrustum() {
   float   proj[16];
   float   modl[16];
   float   clip[16];
   float   t;

   /* Get the current PROJECTION matrix from OpenGL */
   glGetFloatv( GL_PROJECTION_MATRIX, proj );

   /* Get the current MODELVIEW matrix from OpenGL */
   glGetFloatv( GL_MODELVIEW_MATRIX, modl );

   /* Combine the two matrices (multiply projection by modelview) */
   clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
   clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
   clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
   clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

   clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
   clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
   clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
   clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

   clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
   clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
   clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
   clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

   clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
   clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
   clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
   clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];

   /* Extract the numbers for the RIGHT plane */
   frustum[0][0] = clip[ 3] - clip[ 0];
   frustum[0][1] = clip[ 7] - clip[ 4];
   frustum[0][2] = clip[11] - clip[ 8];
   frustum[0][3] = clip[15] - clip[12];

   /* Normalize the result */
   t = sqrt( frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2] );
   frustum[0][0] /= t;
   frustum[0][1] /= t;
   frustum[0][2] /= t;
   frustum[0][3] /= t;

   /* Extract the numbers for the LEFT plane */
   frustum[1][0] = clip[ 3] + clip[ 0];
   frustum[1][1] = clip[ 7] + clip[ 4];
   frustum[1][2] = clip[11] + clip[ 8];
   frustum[1][3] = clip[15] + clip[12];

   /* Normalize the result */
   t = sqrt( frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2] );
   frustum[1][0] /= t;
   frustum[1][1] /= t;
   frustum[1][2] /= t;
   frustum[1][3] /= t;

   /* Extract the BOTTOM plane */
   frustum[2][0] = clip[ 3] + clip[ 1];
   frustum[2][1] = clip[ 7] + clip[ 5];
   frustum[2][2] = clip[11] + clip[ 9];
   frustum[2][3] = clip[15] + clip[13];

   /* Normalize the result */
   t = sqrt( frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2] );
   frustum[2][0] /= t;
   frustum[2][1] /= t;
   frustum[2][2] /= t;
   frustum[2][3] /= t;

   /* Extract the TOP plane */
   frustum[3][0] = clip[ 3] - clip[ 1];
   frustum[3][1] = clip[ 7] - clip[ 5];
   frustum[3][2] = clip[11] - clip[ 9];
   frustum[3][3] = clip[15] - clip[13];

   /* Normalize the result */
   t = sqrt( frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2] );
   frustum[3][0] /= t;
   frustum[3][1] /= t;
   frustum[3][2] /= t;
   frustum[3][3] /= t;

   /* Extract the FAR plane */
   frustum[4][0] = clip[ 3] - clip[ 2];
   frustum[4][1] = clip[ 7] - clip[ 6];
   frustum[4][2] = clip[11] - clip[10];
   frustum[4][3] = clip[15] - clip[14];

   /* Normalize the result */
   t = sqrt( frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2] );
   frustum[4][0] /= t;
   frustum[4][1] /= t;
   frustum[4][2] /= t;
   frustum[4][3] /= t;

   /* Extract the NEAR plane */
   frustum[5][0] = clip[ 3] + clip[ 2];
   frustum[5][1] = clip[ 7] + clip[ 6];
   frustum[5][2] = clip[11] + clip[10];
   frustum[5][3] = clip[15] + clip[14];

   /* Normalize the result */
   t = sqrt( frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2] );
   frustum[5][0] /= t;
   frustum[5][1] /= t;
   frustum[5][2] /= t;
   frustum[5][3] /= t;
} // end extract frustum

/*
* PointInFrustum
* This takes in a x,y,z coordinat, and returns true if this is inside the frustum
* and false if it is outside.  This is used for frustum culling.
*/
bool PointInFrustum( float x, float y, float z ) {
   int p;

   for( p = 0; p < 6; p++ )
      if( frustum[p][0] * x + frustum[p][1] * y + frustum[p][2] * z + frustum[p][3] <= 0 )
         return false;
   return true;
} // end PointInFrustum


/*
* This takes in a car object, and sets the
* display lists to be that of the porsche (entire_car.cpp),
* this calls function in display_list_loader.cpp
*/
void model_load_porsche(Car* the_car) {

	the_car->set_display_lists(DL_get_porsche_entire_car(), 
								DL_get_porsche_back_tires(), 
									DL_get_porsche_left_front(), 
										DL_get_porsche_right_front());

	BoundingBox* testbox = the_car->get_box();
	DL_get_porsche_verticies( testbox );
} // end model_load_porsche()


/* LoadTextureRAW
* load a 256x256 RGB .RAW file as a texture
* I did not write this function myself.  I found it online
* at http://www.nullterminator.net/gltexture.html
*/
GLuint LoadTextureRAW( const char * filename, int wrap ) {
    GLuint texture;
    int width, height;
    void * data;
    FILE * file;

    // open texture data
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;

    // allocate buffer
    width = 32;
    height = 32;
    data = malloc( width * height * 3 );

    // read texture data
    fread( data, width * height * 3, 1, file );
    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &texture );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     wrap ? GL_REPEAT : GL_CLAMP );

    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_RGB, GL_UNSIGNED_BYTE, data );

    // free buffer
    free( data );

    return texture;
} // end LoadTextureRAW


/*
* This loads all necessary car objects, and
* calls the approperiate functions to load the
* display lists
*/
void model_initilize_cars()
{

	// create the users car
	// init building
	glPushMatrix();
		// this calls functions in display_list_loader.cpp
		// and sets the display list integers.
		office_building = DL_get_office_building();
		office_building_2 = DL_get_office_building_2();
		nicehouse_building = DL_get_nice_house();
		coolhouse_building = DL_get_cool_house();
		glass_building_model = DL_get_glassbuilding();
		reliance = DL_get_reliance();
		paper = DL_get_paper();
		parking = DL_get_parking();
		blue = DL_get_blue();
		strip = DL_get_strip();
		glassglass = DL_get_glassglass();
		realsmall = DL_get_realsmall();
		glPopMatrix();
		glPushMatrix();
		buildWorld(handler);
	glPopMatrix();

	// set the user car to the first car object in world.xml
	user_car = car_holder[0];

} // end model_load_porsche()

/*
* This makes all necessary openGL calls
* to set up lighting, etc
*/
void init_opengl() {

	//start lighting values based on time of day(tod)
    glClearColor(0.2, 0.2, 1.0f-abs(tod-12)/12.0f, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_TEXTURE_2D);

	//start lighting values based on time of day(tod)
	ambientLight[0]=0.5f-(fabs(tod-12)/12)/2;
	ambientLight[1]=0.5f-(fabs(tod-12)/12)/2;
	ambientLight[2]=0.5f-(fabs(tod-12)/12)/2;
	diffuseLight[0]=0.5f-(fabs(tod-12)/12)/2;
	diffuseLight[1]=0.5f-(fabs(tod-12)/12)/2;
	diffuseLight[2]=0.5f-(fabs(tod-12)/12)/2;
    GLfloat glfLightSpecular[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    //
    // Add a light to the scene.
    //
    glLightfv (GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv (GL_LIGHT0, GL_SPECULAR, glfLightSpecular);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);

    //
    // Enable depth testing and backface culling.
    //
    glEnable (GL_DEPTH_TEST);
    glDisable (GL_CULL_FACE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE ,1);
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
} // end init_opengl()



/*
* Initilize
* This makes all necessary setup calls, such as
* initilizing the openGL scene, to creating the 
* display lists of 3D models
*/
void Initialize() {
	tod=handler->getWorld()->time_of_day;
	timer = new CHiResTimer;
	timer->Init();
	camera = new Camera();

	// initilize openGL calls
	init_opengl();
	DI_Init(); // initilize direct input

	glPushMatrix();
		// create all necessary cars
		model_initilize_cars();
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPushMatrix();
		#include "init_roads.cpp" // grab all the road functions
	glPopMatrix();

	//  do font stuff
	//	font = new CFont("a",100);
} // end initilize()

/*
* camera_settings
* this makes the approperiate calls
* to move the camera into position
*/
void camera_settings(float mx, float my, float mz) {
	gluLookAt( 0.0f, 1.0f, -2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
} // end camera_settings()

/*
* Render
* Main drawing function
* this is called and draws the world each iteration
*/
void Render() {	
	ambientLight[0]=0.5f-(fabs(tod-12)/12)/2;
	ambientLight[1]=0.5f-(fabs(tod-12)/12)/2;
	ambientLight[2]=0.5f-(fabs(tod-12)/12)/2;
	diffuseLight[0]=0.5f-(fabs(tod-12)/12)/2;
	diffuseLight[1]=0.5f-(fabs(tod-12)/12)/2;
	diffuseLight[2]=0.5f-(fabs(tod-12)/12)/2;
    GLfloat glfLightSpecular[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    //
    // Add a light to the scene.
    //
    glLightfv (GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv (GL_LIGHT0, GL_SPECULAR, glfLightSpecular);

	// increase the time of day, so that it gets dark/light out
	tod+=0.025;
	tod=fmod(tod,24);

	glPushMatrix();

	// get input from user
	Read_Keyboard(); 
	Read_Mouse(); 

	// used to build the map, temporarly disabled
	/*
	if (KeyDown(DIK_F1)) {
		fstream gregsoutput("BUILDING.txt", ios::app);
		gregsoutput<< "<building type=\"1\" x=\""<<floor(user_car->position.x)<<"\" y=\""<<floor(user_car->position.z)<<"\" orientation=\"0\"/>"<<endl;
		gregsoutput.close();
	}

	if (KeyDown(DIK_F2)) {
		fstream gregsoutput("BUILDING.txt", ios::app);
		gregsoutput<< "<building type=\"4\" x=\""<<floor(user_car->position.x)<<"\" y=\""<<floor(user_car->position.z)<<"\" orientation=\"0\"/>"<<endl;
		gregsoutput.close();
	}

	if (KeyDown(DIK_F3)) {
		fstream gregsoutput("BUILDING.txt", ios::app);
		gregsoutput<< "<building type=\"9\" x=\""<<floor(user_car->position.x)<<"\" y=\""<<floor(user_car->position.z)<<"\" orientation=\"0\"/>"<<endl;
		gregsoutput.close();
	}

	if (KeyDown(DIK_F4)) {
		fstream gregsoutput("BUILDING.txt", ios::app);
		gregsoutput<< "<building type=\"10\" x=\""<<floor(user_car->position.x)<<"\" y=\""<<floor(user_car->position.z)<<"\" orientation=\"0\"/>"<<endl;
		gregsoutput.close();
	}
	if (KeyDown(DIK_F5)) {
		fstream gregsoutput("BUILDING.txt", ios::app);
		gregsoutput<< "<building type=\"11\" x=\""<<floor(user_car->position.x)<<"\" y=\""<<floor(user_car->position.z)<<"\" orientation=\"0\"/>"<<endl;
		gregsoutput.close();
	}
	if (KeyDown(DIK_F8)) {
		fstream gregsoutput("BUILDING.txt", ios::app);
		gregsoutput<< "<building type=\"8\" x=\""<<floor(user_car->position.x)<<"\" y=\""<<floor(user_car->position.z)<<"\" orientation=\"0\"/>"<<endl;
		gregsoutput.close();
	}
	if (KeyDown(DIK_F9)) {
		fstream gregsoutput("BUILDING.txt", ios::app);
		gregsoutput<< "<building type=\"7\" x=\""<<floor(user_car->position.x)<<"\" y=\""<<floor(user_car->position.z)<<"\" orientation=\"0\"/>"<<endl;
		gregsoutput.close();
	}*/

	// if spacebar is down, turn on skidding
	if (KeyDown(DIK_SPACE)) {
		user_car->increase_angle();
	}
	else {
		user_car->decrease_angle();
	}
 
	// process all other keyboard commands, see readme.txt for controls
	if (KeyDown(DIK_UP)) {
		user_car->inc_wheel_speed();
	}
	if (KeyDown(DIK_DOWN)) {
		user_car->dec_wheel_speed();
	}
    if (KeyDown(DIK_RIGHT)) { 
		user_car->dec_wheel_angle();
	}
	if (KeyDown(DIK_LEFT)) { 
		user_car->inc_wheel_angle();
	} 
	if (KeyUp(DIK_UP)) {
		user_car->up=false;
	}
	if (KeyUp(DIK_DOWN)) {
		user_car->down=false;
	}
    if (KeyUp(DIK_RIGHT)) { 
		user_car->right=false;
	}
	if (KeyUp(DIK_LEFT)) { 
		user_car->left=false;
	}
	if (KeyDown(DIK_NUMPAD0)) {
		camera->use_predefined_camera(0);
	}
	if (KeyDown(DIK_NUMPAD1)) {
		camera->use_predefined_camera(1);
	}
	if (KeyDown(DIK_NUMPAD2)) {
		camera->use_predefined_camera(2);
	}
	if (KeyDown(DIK_NUMPAD3)) {
		camera->use_predefined_camera(3);
	}
	if (KeyDown(DIK_NUMPAD4)) {
		camera->use_predefined_camera(4);
	}
	if (KeyDown(DIK_NUMPAD5)) {
		camera->use_predefined_camera(5);
	}
	if (KeyDown(DIK_NUMPAD6)) {
		camera->use_predefined_camera(6);
	}
	if (KeyDown(DIK_NUMPAD7)) {
		camera->use_predefined_camera(7);
	}
	if (KeyDown(DIK_NUMPAD8)) {
		camera->use_predefined_camera(8);
	}
	if (KeyDown(DIK_NUMPAD9)) {
		camera->use_predefined_camera(9);
	}
	// turn off collision detection
	if (KeyUp(DIK_C)) {
		if ( user_car->check_collision == true ) {
			user_car->check_collision = false;
		}
		else {
			user_car->check_collision = true;
		}
	}

	// calculate mouse movment used for positioning camera
	float nmx = 0;
	float nmy = 0;
	float nmz = 0;
	Get_Movement(nmx, nmy);
	Get_Wheel_Movement(nmz);
	mx+=nmx;
	my+=nmy;
	mz+=nmz;

	// grab seconds from timer object
	float elapsedSec = timer->GetElapsedSeconds(1);
    glClearColor(0.2, 0.2, 1.0f-fabs(tod-12.0f)/12.0f, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	//font->Print("Greg & Mike");
	
	// animate the car and wrap it around the map if needed
	user_car->Animate( elapsedSec );
	user_car->wrap(xmax,zmax);

	// calculate turns into radians, gta_turn_rad does a sliding camera
	// affect
	float angle_rad = (user_car->car_turn_angle) * (3.14f/180.0f);
	float gta_turn_rad = (user_car->gta_turn) * (3.14f/180.0f);

	// position and point the camera at the car	
	Vector two_pos = user_car->position;
	camera->PositionAtNow(Vector(two_pos.x+(-2.5f*sin(angle_rad-gta_turn_rad)) + (mx/100.0f),0.5f + (my/100.0f),two_pos.z+(-2.5f*cos(angle_rad-gta_turn_rad))) + (mz/100.0f));
	camera->PointAt(Vector(two_pos.x+(2*sin(angle_rad)),0.0f,two_pos.z+(2*cos(angle_rad))));

	// actually position the camera, and get the new frustum coordinates
	camera->Draw();
	ExtractFrustum();

	// draw the user car
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
		user_car->Draw();
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	
	// move light to the front of the car (isn't working correctly at the moment
	GLfloat LightAmbient[]= { 0.0f, 0.0f, 0.0f, 1.0f }; 
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat LightPosition[]= { user_car->position.x, 0.0f, user_car->position.z};	
	GLfloat LightDirection[]= { 0, -1, 0};
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);	
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightDiffuse);		
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);

	// check for collisions
	BoundingBox* testBox = user_car->get_box();

	// loop through each building
	for (int z = 0; z < number_of_buildings; z++ ) {
		// extract this buildings bounding box
		BoundingBox* bTestBox = building_holder[z]->get_box();
		// the user car hits a bounding box, stop the car
		if ( testBox->checkCollision(bTestBox) ) {
			user_car->stop_car();
		}
	}
	// initilize random number
	srand(time(null));

	// loop through each of the cars
	for( int car_index = 1; car_index < number_of_cars; car_index++ ) {
		// extract the bounding box
		BoundingBox* cTestBox = car_holder[car_index]->get_box();

		// use artificial intelligence function to calculate the cars next position
		car_holder[car_index]->AI(road_path,xmax,zmax);
		car_holder[car_index]->Animate(elapsedSec);

		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
			car_holder[car_index]->Draw();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);

		// check for a collision between this car and the user's car
		// if there is a collision bounce them off each other
		if ( testBox->checkCollision(cTestBox)) {
			Vector temp1 = car_holder[car_index]->velocity;
			Vector temp2 = user_car->velocity;
			Vector temp4 = user_car->acceleration;
			user_car->stop_car();
			car_holder[car_index]->stop_car();
			car_holder[car_index]->velocity-=temp2;
			user_car->velocity -= temp1;
		}
	}

	// draw all the buildings and roads
	renderWorld(handler);

	glFlush();
	SwapBuffers(g_HDC);

	glPopMatrix();
} // Render()

/* CleanUp
*  this free's up memory of objects
*/
void CleanUp()
{
	delete user_car;
	delete timer;
	delete camera;

	Release_Mouse(); 
	Release_Keyboard(); 
	Shutdown_CInput8(); 
} // cleanup()

/*
* SetupPixelFormat
* This sets up the pixel format for the monitor device
* This code was taken from the OpenGL Game
* Programming book referenced above
*/
void SetupPixelFormat(HDC hDC)
{
     int nPixelFormat;                       // our pixel format index

     static PIXELFORMATDESCRIPTOR pfd = {
          sizeof(PIXELFORMATDESCRIPTOR),     // size of structure
          1,                                      // default version
          PFD_DRAW_TO_WINDOW |               // window drawing support
          PFD_SUPPORT_OPENGL |               // OpenGL support
          PFD_DOUBLEBUFFER,                  // double buffering support
          PFD_TYPE_RGBA,                     // RGBA color mode
          32,                                     // 32 bit color mode
          0, 0, 0, 0, 0, 0,                  // ignore color bits, non-palettized mode
          0,                                      // no alpha buffer
          0,                                      // ignore shift bit
          0,                                      // no accumulation buffer
          0, 0, 0, 0,                             // ignore accumulation bits
          16,                                     // 16 bit z-buffer size
          0,                                      // no stencil buffer
          0,                                      // no auxiliary buffer
          PFD_MAIN_PLANE,                         // main drawing plane
          0,                                      // reserved
          0, 0, 0 };                              // layer masks ignored

     nPixelFormat = ChoosePixelFormat(hDC, &pfd); // choose best matching pixel format

     SetPixelFormat(hDC, nPixelFormat, &pfd);          // set pixel format to device context
} // SetupPixelFormat()

/*
* WndProc
* This is the event handler, this is what is called
* when windows passes events to the openGL program
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static HGLRC hRC;                       // rendering context
     static HDC hDC;                              // device context
     char string[] = "Hello, world!";   // text to be displayed
     int width, height;                      // window width and height
     int oldMouseX, oldMouseY;

     switch(message)
	 {
          case WM_CREATE:                         // window is being created

               hDC = GetDC(hwnd);            // get current window's device context
               g_HDC = hDC;
               SetupPixelFormat(hDC);        // call our pixel format setup function

               // create rendering context and make it current
               hRC = wglCreateContext(hDC);
               wglMakeCurrent(hDC, hRC);

               return 0;
               break;

          case WM_CLOSE:                     // windows is closing

               // deselect rendering context and delete it
               wglMakeCurrent(hDC, NULL);
               wglDeleteContext(hRC);

               // send WM_QUIT to message queue
               PostQuitMessage(0);

               return 0;
               break;

          case WM_SIZE:
               height = HIWORD(lParam);      // retrieve width and height
               width = LOWORD(lParam);

               if (height==0) {                    // don't want a divide by zero
                    height=1;
               }

               glViewport(0, 0, width, height);        // reset the viewport to new dimensions
               glMatrixMode(GL_PROJECTION);            // set projection matrix current matrix
               glLoadIdentity();                            // reset projection matrix

               // calculate aspect ratio of window
               gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,1.0f,25.0f);

               glMatrixMode(GL_MODELVIEW);                  // set modelview matrix
               glLoadIdentity();                            // reset modelview matrix

               return 0;
               break;

          case WM_MOUSEMOVE:
               // save old mouse coordinates
               oldMouseX = mouseX;
               oldMouseY = mouseY;

               // get mouse coordinates from Windows
               mouseX = LOWORD(lParam);
               mouseY = HIWORD(lParam);

               break;

          default:
               break;
     }

     return (DefWindowProc(hwnd, message, wParam, lParam));
} // WndProc()

/*
* render World -- loops through building array and
* displays them
*/
void renderWorld(SAXMapHandler *handler) {
	glColor3f(0.0f,1.0f-fabs(tod-12)/12.0f,0.0f);
	SAXMapHandler::World *world = handler->getWorld();
	
	// save state of textures
	bool en=false;
	if(glIsEnabled(GL_TEXTURE_2D)) {
		en=true;
		glDisable(GL_TEXTURE_2D);
	}

	// draw the green floor of the world
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
		glVertex3f(0,-0.17,world->y);
		glVertex3f(world->x,-0.17,world->y);
		glVertex3f(world->x,-0.17,0);
		glVertex3f(0,-0.17,0);
	glEnd();

	if(en) 	{
		glEnable(GL_TEXTURE_2D);
	}
	glEnable(GL_LIGHTING);
	glColor3f(1,1,1);

	bool render_building = false;
	BoundingBox* testBox = NULL;
	Plane* testPlane = NULL;

	// loop through each building
	for ( int i = 0; i < number_of_buildings; i++ ) {
		render_building = false;
		// get bounding box of this building
		testBox = building_holder[i]->get_box();
		// check each plane of this bounding box
		for ( int j = 0; j < 6; j++ ) {
			testPlane = testBox->planes[j];
			if ( !render_building ) {
				// check each point of this plane
				for ( int k = 0; k < 4; k++ ) {
					if ( !render_building ) {
						// if this building is in our frustum
						if ( PointInFrustum( testPlane->points[k][0] + building_holder[i]->x, 0.0f, testPlane->points[k][2] +  + building_holder[i]->y )) {
							render_building = true;
							// draw it
							building_holder[i]->Draw();
						} // end if
					} // end if
				} // end for
			} // end if
		} // end for
	} // end for

	// grab linked list of all roads
	SAXMapHandler::Road *roads = handler->getRoads();
	int x;
	int y;
	int type;
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	if ( KeyDown(DIK_G)) {
		glEnable(GL_COLOR_MATERIAL);
	}
	else if (KeyUp(DIK_G)) {
		glDisable(GL_COLOR_MATERIAL);
	}
	glEnable(GL_LIGHTING);

	while(roads!=null) {
		x=roads->x;
		y=roads->y;
		// if any of this road is in our frustum, draw it
		if ( PointInFrustum( x, 0.0f, y) || PointInFrustum( x + 1, 0.0f, y + 1 ) || PointInFrustum(x, 0.0f, y+1) || PointInFrustum(x+1,0.0f,y) ) {
			type=roads->type;
			glPushMatrix();
				glTranslatef(x, -0.16, y);
				glEnable(GL_TEXTURE_2D);
				glDisable(GL_LIGHTING);
				glDisable(GL_BLEND);

				// check road type to determine which type to draw
				if(type==0) {
					glCallList( road_display_list0 );
				}
				else if(type==1) {
					glCallList( road_display_list1 );
				}
				else if(type==2) {
					glCallList( road_display_list2 );
				}
				else if(type==3) {
					glCallList( road_display_list3 );
				}
				else if(type==4) {
					glCallList( road_display_list4 );
				}
				else if(type==5) {
					glCallList( road_display_list5 );
				}
				else if(type==6) {
					glCallList( road_display_list6 );
				}
				else if(type==7) {
					glCallList( road_display_list7 );
				}
				else if(type==8) {
					glCallList( road_display_list8 );
				}
				else if(type==9) {
					glCallList( road_display_list9 );
				}
				else if(type==10){
					glCallList( road_display_list10 );
				}
				else if(type==11){
					glCallList( road_display_list11 );
				}
				else if(type==12) {
					glCallList( road_display_list12 );
				}
				else if(type==13) {
					glCallList( road_display_list13 );
				}
				else if(type==14) {
					glCallList( road_display_list14 );
				}
			glPopMatrix();
		}
		roads=roads->next;
	}
	glEnable(GL_LIGHTING);
} // end renderWorld()

/*
* buildWorld
* this goes through the world.xml file and stores the correct objects
* in car_holder and building_holder
*/
void buildWorld(SAXMapHandler *handler) {

	BoundingBox* testbox = NULL;

	// grab linked list of all cars
	SAXMapHandler::Car *cars = handler->getCars();
	number_of_cars = SAXMapHandler::num_cars;
	// create array for cars
	car_holder = (Car**)calloc(number_of_cars, sizeof(Car*));

	// loop through each car
	for (int j = 0; j < number_of_cars; j++ ) {
		// create a new car object, and set its properities
		car_holder[j] = new Car();
		car_holder[j]->type = cars->type;
		car_holder[j]->orientation = cars->orientation;
		car_holder[j]->position.x = cars->x;
		car_holder[j]->position.y = 0.0f;
		car_holder[j]->position.z = cars->y;
		car_holder[j]->next_position.x = cars->x;
		car_holder[j]->next_position.y = 0.0f;
		car_holder[j]->next_position.z = cars->y;

		// set two different car types (red or black)
		if ( cars->type == 0 ){
			car_holder[j]->set_display_lists(DL_get_porsche_entire_car(), 
									DL_get_porsche_back_tires(), 
										DL_get_porsche_left_front(), 
											DL_get_porsche_right_front());

			testbox = car_holder[j]->get_box();

			// set this cars bounding box
			DL_get_porsche_verticies( testbox );
		}
		else if (cars->type == 1 ) {

			car_holder[j]->set_display_lists(DL_get_darkcar(), 
									DL_get_porsche_back_tires(), 
										DL_get_porsche_left_front(), 
											DL_get_porsche_right_front());

			testbox = car_holder[j]->get_box();
			DL_get_darkcar_verticies( testbox );
		}
		cars = cars->next;
	}

	// loop through each road, and set the road_path which is used by the 
	// artificial intelligence of the program, initially set all to false
	int x=handler->getWorld()->x;
	int y=handler->getWorld()->y;
	road_path = (bool**) calloc(y,sizeof(int));
	for(int i=0;i<y;i++) {
		road_path[i]=(bool*)calloc(x,sizeof(bool));
		for(int j=0;j<x;j++) {
			road_path[i][j]=false;
		}
	}

	// loop through each road, and set the road_path which is used by the 
	// artificial intelligence of the program
	SAXMapHandler::Road *roads = handler->getRoads();
	while(roads!=null) {
		if(roads->type==0||roads->type==1||roads->type==2) {
			road_path[roads->y][roads->x]=true;
		}
		roads=roads->next;
	}

	xmax=x;
	zmax=y;

	// loop through each building
	SAXMapHandler::Building *buildings = handler->getBuildings();
	number_of_buildings = SAXMapHandler::num_buildings;
	building_holder = (Building**)calloc(number_of_buildings,sizeof(Building*));
	testbox = NULL;

	for (i = 0; i < number_of_buildings; i++ ) {
		// create this building's object, and set it properities
		building_holder[i] = new Building();
		building_holder[i]->x = buildings->x;
		building_holder[i]->y = buildings->y;
		building_holder[i]->type = buildings->type;
		building_holder[i]->orientation = buildings->orientation;
		testbox = building_holder[i]->get_box();

		// check building type (1 of 11), and 
		// set it's bounding box using it's verticies
		if ( buildings->type == 0 ) {
			// no type zero
		}
		else if ( buildings->type == 1 ) {
			building_holder[i]->list=office_building;
			DL_get_office_verticies( testbox );
		}
		else if ( buildings->type == 2 ) {
			building_holder[i]->list=office_building_2;
			DL_get_office_2_verticies( testbox );
		}
		else if ( buildings->type == 3 ) {
			building_holder[i]->list=nicehouse_building;
			DL_get_nicehouse_verticies( testbox );
		}
		else if (buildings->type == 4 ) {
			building_holder[i]->list=coolhouse_building;
			DL_get_coolhouse_verticies( testbox );
		}
		else if (buildings->type == 5 ) {
			building_holder[i]->list=glass_building_model;
			DL_get_glass_verticies( testbox );
		}
		else if (buildings->type == 6 ) {
			building_holder[i]->list=reliance;
			DL_get_reliance_verticies( testbox );
		}
		else if (buildings->type == 7 ) {
			building_holder[i]->list=paper;
			DL_get_paper_verticies( testbox );
		}
		else if (buildings->type == 8 ) {
			building_holder[i]->list=parking;
			DL_get_parking_verticies( testbox );
		}
		else if (buildings->type == 9 ) {
			building_holder[i]->list=blue;
			DL_get_blue_verticies( testbox );
		}
		else if (buildings->type == 10 ) {
			building_holder[i]->list=strip;
			DL_get_strip_verticies( testbox );
		}
		else if (buildings->type == 11 ) {
			building_holder[i]->list=blue;
			DL_get_blue_verticies( testbox );
		}
		else if (buildings->type == 12 ) {
			building_holder[i]->list=realsmall;
			DL_get_realsmall_verticies( testbox );
		}
		
		buildings=buildings->next;
	} // end for

} // end buildWorld()

/*
* WinMain
* Main windows function, this is what executes first
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
						LPSTR lpCmdLine, int nShowCmd) {
     WNDCLASSEX windowClass;       // window class

     MSG          msg;                  // message
     bool    done;            // flag saying when our app is complete
	 g_Instance = hInstance;

	handler = new SAXMapHandler();

	char *systemid = "world.xml";

	if(handler->executeParse(systemid)==0){
		cout<<"\n\nParse Success!"<<endl;
	}
	else{
		cout<<"\n\nParse Failed!"<<endl;
	}

	// get our instance handle
	g_Instance = GetModuleHandle(NULL);

     // fill out the window class structure
     windowClass.cbSize            = sizeof(WNDCLASSEX);
     windowClass.style             = CS_HREDRAW | CS_VREDRAW;
     windowClass.lpfnWndProc       = WndProc;
     windowClass.cbClsExtra        = 0;
     windowClass.cbWndExtra        = 0;
     windowClass.hInstance         = hInstance;
     windowClass.hIcon             = LoadIcon(NULL, IDI_APPLICATION); // default icon
     windowClass.hCursor           = LoadCursor(NULL, IDC_ARROW);          // default arrow
     windowClass.hbrBackground     = NULL;                                      // don't need background
     windowClass.lpszMenuName = NULL;                                      // no menu
     windowClass.lpszClassName     = "MyClass";
     windowClass.hIconSm           = LoadIcon(NULL, IDI_WINLOGO);          // windows logo small icon

     // register the windows class
     if (!RegisterClassEx(&windowClass))
          return 0;

     // class registered, so now create our window
     hwnd = CreateWindowEx(NULL,                                           // extended style
                                "MyClass",                                 // class name
                                "3D World - Greg and Mike",      // app name
                                WS_OVERLAPPEDWINDOW | WS_VISIBLE |    // style
                                WS_SYSMENU | WS_CLIPCHILDREN |
                                WS_CLIPSIBLINGS,
                                100, 100,                                       // x,y coordinate
                                800, 600,                                       // width, height
                                NULL,                                           // handle to parent
                                NULL,                                           // handle to menu
                                hInstance,                                 // application instance
                                NULL);                                     // no extra params

     // check if window creation failed (hwnd would equal NULL)
     if (!hwnd) {
          return 0;
	 }

     ShowWindow(hwnd, SW_SHOW);              // display the window
     UpdateWindow(hwnd);                     // update the window

     done = false;                           // intialize the loop condition variable

     Initialize();			// initilize openGL and display lists
     ShowCursor(FALSE);		// turn off mouse


     // main message loop
     while (!done) {
          PeekMessage(&msg, hwnd, NULL, NULL, PM_REMOVE);

          if (msg.message == WM_QUIT) {      // do we receive a WM_QUIT message?
               done = true;                  // if so, time to quit the application
          }
          else {

               Render();                     // render world
   			   SwapBuffers(g_HDC);

               TranslateMessage(&msg);       // translate and dispatch to event queue
               DispatchMessage(&msg);
          }
     } // end while

     CleanUp();			// clean up free memory
     ShowCursor(TRUE);  // turn mouse back on

     return msg.wParam;
} // end WinMain
