/* ---------------------------------------------------------------------------
** This file calls all the cpp files containing openGL commands generated
** by 3D Explorer (http://www.righthemisphere.com), and compiles them into
** Display Lists.
**
** display_list_loader.cpp
**
** Authors: Greg Bender
**          Michael Krauklis
** -------------------------------------------------------------------------*/

#include <windows.h>                         // standard Windows app
#include <gl/gl.h>
#include <vector>
#include "boundingbox.cpp"

/* START PORSCHE CAR INCLUDE FILES */
#include "thebuildings/back_tires.cpp"
#include "thebuildings/entire_car.cpp"
#include "thebuildings/left_front.cpp"
#include "thebuildings/right_front.cpp"
/* END PORSCHE CAR INCLUDE FILES */

/* Start Office Building */
#include "thebuildings/h10.cpp"
#include "thebuildings/office22.cpp"
#include "thebuildings/nicehouse.cpp"
#include "thebuildings/house2.cpp"
#include "thebuildings/smallhouse.cpp"
#include "thebuildings/reliance.cpp"
#include "thebuildings/paper.cpp"
#include "thebuildings/parking.cpp"
#include "thebuildings/bluebuilding.cpp"
#include "thebuildings/stripbuilding.cpp"
#include "thebuildings/glass.cpp"
#include "thebuildings/realsmall.cpp"
#include "thebuildings/darkcar.cpp"

GLfloat params_min[1];
GLfloat params_mag[1];

// these functions save and restore the texture filters, cause some display
// lists mess them up
void save_it_all(){
	glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params_min);
	glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params_mag);
}
void restore_it_all(){
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params_min);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params_mag);
}

/* GLOBAL DISPLAY_LIST FUNCTIONS */
/* each of these sets a display list based on files in the
* thebuildings director
*/
GLint DL_get_glassglass() {
    save_it_all();
	GLint building = glassb::Gen3DObjectList();
	restore_it_all();
	return building;
}
GLint DL_get_realsmall() {
    save_it_all();
	GLint building = real_small::Gen3DObjectList();
	restore_it_all();
	return building;
}
GLint DL_get_blue() {
    save_it_all();
	GLint building = blue_building::Gen3DObjectList();
	restore_it_all();
	return building;
}
GLint DL_get_strip() {
    save_it_all();
	GLint building = stripbuilding::Gen3DObjectList();
	restore_it_all();
	return building;
}
GLint DL_get_parking() {
    save_it_all();
	GLint building = parkingmeter::Gen3DObjectList();
	restore_it_all();
	return building;
}
GLint DL_get_paper() {
    save_it_all();
	GLint building = paper_paper::Gen3DObjectList();
	restore_it_all();
	return building;
}
GLint DL_get_reliance() {
    save_it_all();
	GLint building = reliance_building::Gen3DObjectList();
	restore_it_all();
	return building;
}
GLint DL_get_glassbuilding() {
    save_it_all();
	GLint building = glass_building::Gen3DObjectList();
	restore_it_all();
	return building;
}
GLint DL_get_nice_house() {
	save_it_all();
	GLint building = nicehouse::Gen3DObjectList();
	restore_it_all();
	return building;
}
GLint DL_get_cool_house() {
	save_it_all();
	GLint building = coolhouse::Gen3DObjectList();
	restore_it_all();
	return building;
}
GLint DL_get_office_building() {
	GLint building = office::Gen3DObjectList();
	return building;
}
GLint DL_get_office_building_2() {
	save_it_all();
	GLint building = office_2::Gen3DObjectList();
	restore_it_all();
	return building;
}


/* BoundingBox Setup */
/* each of these functions takes in a bounding box (passed in from main.cpp
* and this bounding box is created based on the verticies in the display list
*/
void DL_get_porsche_verticies(BoundingBox* box) {
	box->set_verticies(porsche_entire_car::vertices,sizeof(porsche_entire_car::vertices)/ (3*sizeof(float)));
}
void DL_get_darkcar_verticies(BoundingBox* box) {
	box->set_verticies(darkcar::vertices,sizeof(darkcar::vertices)/ (3*sizeof(float)));
}
void DL_get_office_verticies(BoundingBox* box) {
	box->set_verticies(office::vertices,sizeof(office::vertices)/ (3*sizeof(float)));
}
void DL_get_office_2_verticies(BoundingBox* box) {
	box->set_verticies(office_2::vertices,sizeof(office_2::vertices)/ (3*sizeof(float)));
}
void DL_get_nicehouse_verticies(BoundingBox* box) {
	box->set_verticies(nicehouse::vertices,sizeof(nicehouse::vertices)/ (3*sizeof(float)));
}
void DL_get_coolhouse_verticies(BoundingBox* box) {
	box->set_verticies(coolhouse::vertices,sizeof(coolhouse::vertices)/ (3*sizeof(float)));
}
void DL_get_glass_verticies(BoundingBox* box) {
	box->set_verticies(glass_building::vertices,sizeof(glass_building::vertices)/ (3*sizeof(float)));
}
void DL_get_reliance_verticies(BoundingBox* box) {
	box->set_verticies(reliance_building::vertices,sizeof(reliance_building::vertices)/ (3*sizeof(float)));
}
void DL_get_paper_verticies(BoundingBox* box) {
	box->set_verticies(paper_paper::vertices,sizeof(paper_paper::vertices)/ (3*sizeof(float)));
}
void DL_get_parking_verticies(BoundingBox* box) {
	box->set_verticies(parkingmeter::vertices,sizeof(parkingmeter::vertices)/ (3*sizeof(float)));
}
void DL_get_blue_verticies(BoundingBox* box) {
	box->set_verticies(blue_building::vertices,sizeof(blue_building::vertices)/ (3*sizeof(float)));
}
void DL_get_strip_verticies(BoundingBox* box) {
	box->set_verticies(stripbuilding::vertices,sizeof(stripbuilding::vertices)/ (3*sizeof(float)));
}
void DL_get_glassglass_verticies(BoundingBox* box) {
	box->set_verticies(glassb::vertices,sizeof(glassb::vertices)/ (3*sizeof(float)));
}
void DL_get_realsmall_verticies(BoundingBox* box) {
	box->set_verticies(real_small::vertices,sizeof(real_small::vertices)/ (3*sizeof(float)));
}
GLint DL_get_porsche_back_tires() {
	GLint back_tires = porsche_back_tires::Gen3DObjectList();
	return back_tires;
}
GLint DL_get_porsche_entire_car() {
	save_it_all();
	return porsche_entire_car::Gen3DObjectList();
	restore_it_all();
}
GLint DL_get_darkcar() {
	save_it_all();
	return darkcar::Gen3DObjectList();
	restore_it_all();
}
GLint DL_get_porsche_left_front() {
	GLint left_front = porsche_left_front::Gen3DObjectList();

	return left_front;
}
GLint DL_get_porsche_right_front() {
	GLint right_front = porsche_right_front::Gen3DObjectList();
	return right_front;
}



