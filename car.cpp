/* ---------------------------------------------------------------------------
** This is a car object.  This contains all information about
** the user car and all computer controlled cars.  In the main.cpp
** file there is a car_holder array that holds of these Car objects.
** This object provides the interface for acceleration/deceleration/
** and turning of the car.
**
** car.cpp
**
** Authors: Greg Bender
**          Michael Krauklis
** -------------------------------------------------------------------------*/
#ifndef __CAR_C_INCLUDED__
#define __CAR_C_INCLUDED__

// Object.h is a class Car inherits from that contains several
// function that all objects in our world will have
// such as a Draw and Animate function
#include "object.h"

// Other standard includes
#include "wheel.cpp"
#include "XMLImport/global.hpp"
#include <iostream.h>
#include <fstream.h>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/*
* Car object, represents all aspects of a car in the 3D world.
*/
class Car :public Object {
	public :

		/*
		* Car constructor
		* set default velocity,acc,position vectors
		* and create a new boundingbox
		*/
		Car() {

			box = new BoundingBox();
			
			position = Vector(0.0f, 0.4f, 0.0f);
			next_position=Vector(0.0f, 0.0f, 0.0f); 
			velocity = Vector(0.0f, 0.0f, 0.0f);
			last_velocity = Vector(0.0f, 0.0f, 0.0f);
			acceleration = Vector(0.0f, 0.0f, 0.0f);
			deceleration = Vector(0.0f, 0.0f, 0.0f); // deceleration due to friction

			last_safe_x=-1;
			last_safe_z=-1;

			// set default boolean values
			waypoint = false;
			do_skid = false;
			skid_link = false;
			check_collision = true;
			collision = false;
			changing_dir = false;

			// linked list used for skidding
			skid=null;
			skid_last=null;

			// car display list
			entire_car = 0;

			// angle for each unit of turn
			delta_turn = 1.5f;
			direction = 0.0f;	// direction car is traveling
								// 1 for forward, -1 for backwards
		
			car_turn_angle = 0.0f;	// angle the car has turned
									// in the xz plane
			
			gta_turn = 0.0f;		// angle used for
									// 'following' the camera behind the car

			facing_dir = 2;
			car_angle = 0.0f;
			rock_val = 0.0f;
			dca=0;
			up=false;
			down=false;
			right=false;
			left=false;
			MAX_TURN=20.0f;
			MIN_TURN=0.05f;
			MAX_A=0.05f;
			MAX_V=0.5f;
			t = "\t";

			// create wheel objects
			wheelclass_left_front = new Wheel();
			wheelclass_right_front = new Wheel();
			wheelclass_back = new Wheel();

			// move the wheels to the correct areas of the car, instead
			// of having them show up in the middle
			wheelclass_left_front->set_translate(Vector(  0.17f, -0.07f, 0.32f ));
			wheelclass_right_front->set_translate(Vector(  -0.17f, -0.07f, 0.32f ));
		} // end Car()

		/*
		* Car deconstructor, deletes the wheel objects
		*/
		~Car() {
			glDeleteLists(entire_car, 1);
			
			delete wheelclass_left_front;
			delete wheelclass_right_front;
			delete wheelclass_back;
		} // end ~Car()

		/*
		*	grab this cars bounding box
		*/
		BoundingBox* get_box() {
			return box;
		}

		/*
		* Called from main to set what this cars display lists will represent
		*/
		void set_display_lists(GLint a_entire_car, GLint a_back_tires,
									GLint a_left_front, GLint a_right_front) {

			entire_car = a_entire_car;

			wheelclass_left_front->set_display_lists(a_left_front);
			wheelclass_right_front->set_display_lists(a_right_front);
			wheelclass_back->set_display_lists(a_back_tires);
		}  // end set_display_lists()

		/*
		* used to stop car when there is a collision
		* this sets all vectors to zero
		*/
		void stop_car() {

			if (check_collision == true ) {
				collision=true;
				velocity=-velocity * (0.15f); 
				acceleration=-acceleration * (0.15f); 
				direction = -direction;
				deceleration=Vector(0.0f, 0.0f, 0.0f); 
				next_position = position;
			}
			else {
				collision = false;
			}
		} // end stop_car
	
		/*
		* decrease wheel angle simulates a right turn
		* in the car.. the if statements are used to
		* make the car turn differently if it is traveling
		* backwards.
		*/
		void dec_wheel_angle() {
		
			last_angle = car_turn_angle;
			GLfloat length = velocity.Length();

			// simulate camera affect on car
			// car is traveling forwards
			if ( direction == 1.0f ) {
				if ( gta_turn > -20.0f ) {
					gta_turn -= 1.0f;
				}
				else {
					gta_turn -= 0.5f;
				}
			}
			// car is traveling backwards
			else if ( direction == -1.0f ) {
				if ( gta_turn > -20.0f ) {
					gta_turn -= 1.0f;
				}
				else 
				{
					gta_turn -= 0.5f;
				}
			}
	
			// make car actually turn
			// car is traveling backwards
			if ( direction == -1.0f ) {

				if ( rock_val > -20 ) {
					rock_val -=2;
				}

				// also turn this cars bounding box
				box->rotatebox( last_angle, last_velocity);

				if(length!=0) {
					car_turn_angle += delta_turn;
				}
			}
			// car is traveling forwards
			else if (direction == 1.0f) {

				if ( rock_val < 20 ) {
					rock_val +=2;
				}

				box->rotatebox( last_angle, last_velocity);

				if(length!=0) {
						car_turn_angle -= delta_turn;
				}
			}	
		} // end dec_wheel_angle

		/*
		* increase wheel angle, performs same function as decrease wheel
		* angle, except in reverse
		*/
		void inc_wheel_angle() {
			last_angle = car_turn_angle;
			GLfloat length = velocity.Length();

			if ( direction == 1.0f ) {
				if ( gta_turn < 20.0f ) {
					gta_turn += 1.0f;
				}
				else  {
					gta_turn += 0.5f;
				}
			}
			else if ( direction == -1.0f ) {
				if ( gta_turn < 20.0f ) {
					gta_turn += 1.0f;
				}
				else  {
					gta_turn += 0.5f;
				}
			}
			if ( direction == -1.0f ) {
				box->rotatebox( last_angle, last_velocity);
				if(length!=0) {
					car_turn_angle -= delta_turn;
				}
				if ( rock_val < 20 ) {
					rock_val += 2;
				}
			}
			else if (direction == 1.0f){
				box->rotatebox( last_angle, last_velocity);
				if(length!=0) {
					car_turn_angle += delta_turn;
				}

				if ( rock_val > -20 ) {
					rock_val -= 2;
				}
			}
		}

		void dec_wheel_speed() {
			down = true;
			up = false;
			if ( direction == 0.0f ) {
				direction = -1.0f;
				changing_dir = true;
				deceleration = Vector(0.0f, 0.0f, 0.0f);
			}
			
			if ( direction == 1.0f ) {
				changing_dir = true;
				deceleration += Vector(-1.3f, -1.3f, -1.3f);
			}
			else {
				changing_dir = false;
				acceleration += Vector(-1.3f, -1.3f, -1.3f);
			}
		}
		void inc_wheel_speed() {
			
			up = true;
			down = false;

			if ( direction == 0.0f ) {
				direction = 1.0f;
				changing_dir = true;
				deceleration = Vector(0.0f, 0.0f, 0.0f);
			}
			
			if ( direction == -1.0f ) {
				changing_dir = true;
				deceleration += Vector(1.3f, 1.3f, 1.3f);
			}
			else {
				changing_dir = false;
				acceleration += Vector(1.3f, 1.3f, 1.3f);
			}


		}



	void Draw() {

		glPushMatrix();
			box->Draw();
		glPopMatrix();
		glPushMatrix();
			glTranslatef( position.x, position.y, position.z);
			glRotatef( car_turn_angle, 0.0f, 1.0f, 0.0f );
		//	glRotatef( rock_val, 0.0f, 0.0f, 1.0f);
			glCallList(entire_car);
		glPopMatrix();


		int sss=0;
		Skid *ts=skid;
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glColor3f(0,0,0);
		glLineWidth(3.0f);
		//glEnable(GL_LINE_SMOOTH);
		//iterate through skid linked list
		bool doit=true;
		float dx,dz;
		while(ts!=null)
		{
			if(doit)
			{
				dx=ts->x-ts->next->x;
				dz=ts->z-ts->next->z;

				dx=dx/20;
				dz=dz/20;
				doit=false;
			}
			else
			{
				doit=true;
			}

			if(ts->next!=null)
			{
				if(ts->next->next!=null)
				{
					if(ts->next->next->linked)
					{
						
						glBegin(GL_LINES);
							glVertex3f(ts->next->next->x,-0.15f,ts->next->next->z);
							glVertex3f(ts->x,-0.15f,ts->z);
						glEnd();
						glBegin(GL_LINES);
							glVertex3f(ts->next->next->x-dx,-0.15f,ts->next->next->z-dz);
							glVertex3f(ts->x-dx,-0.15f,ts->z-dz);
						glEnd();
						glBegin(GL_LINES);
							glVertex3f(ts->next->next->x+dx,-0.15f,ts->next->next->z+dz);
							glVertex3f(ts->x+dx,-0.15f,ts->z+dz);
						glEnd();
					}
				}
			}/*
			//draw a patch if the skid is not connected
			//this is disabled
			else
			{
				glBegin(GL_QUADS);
					glVertex3f(ts->x+0.1f,-0.15f,ts->z+0.1f);
					glVertex3f(ts->x+0.1f,-0.15f,ts->z-0.1f);
					glVertex3f(ts->x-0.1f,-0.15f,ts->z-0.1f);
					glVertex3f(ts->x-0.1f,-0.15f,ts->z+0.1f);
				glEnd();
			}*/

			//garbage collection of skids once they time out
			ts->timer++;
			if(ts->timer>250)
			{
				ts=ts->next;
				delete skid;
				skid=ts;
			}
			else
			{
				ts=ts->next;
			}
		}
		//glDisable(GL_LINE_SMOOTH);
		//glLineWidth(1);


		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glPushMatrix();
			glTranslatef( position.x, position.y, position.z);
			glRotatef( car_turn_angle, 0.0f, 1.0f, 0.0f );
			wheelclass_left_front->Draw();
			wheelclass_right_front->Draw();
			wheelclass_back->Draw();
		glPopMatrix();

		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
	} // end Draw()

	void make_skid() {
		//if we want to create a skid
		if ( do_skid ) {

			//create two new skids
			//one for each of the two back wheels
			Skid *ns=new Skid;
			Skid *nns=new Skid;
			//link the two skids
			ns->next=nns;
			nns->next=null;
			//linked?
			ns->linked=skid_link;
			nns->linked=skid_link;
			//set timers to -
			ns->timer=0;
			nns->timer=0;
			//calculate angle in radians
			GLfloat an=car_turn_angle;
			an=(float)fmod(an,360.0f);
			int dif=-1;
			if(an<0) {
				an=an+360.0f;
			}
			//if(an>180) {
				//dif=1;
				//an-=180;
			//}

			an=an*3.14f/180.0f;

			//calculate positions based on car size(constant) and rotation of car
			ns->x=position.x+dif*0.3623534f*(float)sin(an+0.488311f);
			nns->x=position.x+dif*0.3623534f*(float)sin(an-0.488311f);
			ns->z=position.z+dif*0.3623534f*(float)cos(an+0.488311f);
			nns->z=position.z+dif*0.3623534f*(float)cos(an-0.488311f);

			//link to the member linked list
			if(skid!=null)
			{
				skid_last->next=ns;
				skid_last=nns;
			}
			else
			{
				skid=ns;
				skid_last=nns;
			}
			//the_last_skid=ns;
			skid_link=true;
		}
	}

	//e-break
	void increase_angle() {
		delta_turn = 4.5;
		do_skid = true;
		deceleration += Vector(0.8f, 0.8f, 0.8f);
	}

	//no e-break
	void decrease_angle() {
		do_skid = false;
		skid_link=false;
		delta_turn = 1.5;
		deceleration = Vector(0.0f, 0.0f, 0.0f);
	}

	void go_to(scalar_t deltaTime) {
//		Vector direction = Vector(30.0f, 0.0f, 0.0f);
		
			inc_wheel_speed();
//		if ( position.Angle(direction) > 5.0f ) {
			inc_wheel_angle();
			Animate(deltaTime);
//		}


	}

	//calculate next so we don't get stuck inside buildings and cars
	void calculate_next(scalar_t deltaTime) {

		last_elapsed = deltaTime;

		float time = deltaTime;
		//get car turn angle in radians
		GLfloat calculated_angle = car_turn_angle * (3.14f / 180.0f);
		
		//calculate cos and sin once for efficiency
		GLfloat calculated_angle_cos = (float)cos(calculated_angle);
		GLfloat calculated_angle_sin = (float)sin(calculated_angle);

		//figure out gta stuff
		if ( (gta_turn > 0.0f)  && (velocity.Length() > 0.0f) ) {

			if ( !changing_dir ) {
				gta_turn = (gta_turn - 0.5f);
			}
		}
		else if ( (gta_turn < 0.0f) && (velocity.Length() > 0.0f) ) {
			if ( !changing_dir ) {
				gta_turn = (gta_turn + 0.5f);
			}
		}

		//gta max and min fixing
		if ( gta_turn > 20.0f ) {
			gta_turn = 20.0f;
		}
		else if ( gta_turn < -20.0f ) {
			gta_turn = -20.0f;
		}
		
		//move wheels
		wheelclass_left_front->wheel_angle = gta_turn * 1.5f;
		wheelclass_right_front->wheel_angle = gta_turn * 1.5f;			

		GLfloat calculated_gta_angle = gta_turn * (3.14f / 180.0f);
		calculated_gta_angle=0.0f;

		//physics stuff
		acceleration = (direction * Vector( acceleration.Length() * calculated_angle_sin, 0.0f, acceleration.Length() * calculated_angle_cos));
		last_velocity = velocity;
		velocity = direction * Vector( velocity.Length() * (float)sin( calculated_angle + (3.0f * calculated_gta_angle)), 0.0f, velocity.Length() * (float)cos( calculated_angle + (3.0f * calculated_gta_angle)));

		deceleration = -direction * Vector(deceleration.Length() * calculated_angle_sin, 0.0f, deceleration.Length() * calculated_angle_cos);

		//always call make skid, member var boolean tells weither or not skids are created
		make_skid();

		acceleration += deceleration + -(velocity * 0.4f);

		if ( velocity.Length() < 0.5f ) {
			direction = 0.0f;
			deceleration = Vector(0.0f, 0.0f, 0.0f);
		}

		next_position += velocity * time + acceleration * (time * time * 0.5f);
		velocity += acceleration * time;

		if ( type == 1 ) {
			velocity = 0.5f * velocity;
		}

		if ( rock_val > 0.0f ) {
			rock_val--;
		}
		else if ( rock_val < 0.0f ) {
			rock_val++;
		}

		//move bounding box
		if ( type==0 ) {
			box->translate(next_position.x, next_position.y, next_position.z );
		}
		else {
			box->translate(position.x, position.y, position.z );
		}	
		
		//old position stuff, before we did the next position forcasting
		/*
		if(position.x<0)
		{
			//position.x=xmax-1;
			next_position.x=xmax-1;
		}
		if(position.z<0)
		{
			//position.z=zmax-1;
			next_position.z=zmax-1;
		}
		if(position.z>=zmax-1)
		{
			//position.z=(float)1.0f;
			next_position.z=(float)1.0f;
		}
		if(position.x>=xmax-1)
		{
			//position.x=(float)1.0f;
			next_position.x=(float)1.0f;
		}*/
	}

	//check to see if we wrap around off the map
	void wrap(int xmax,int zmax)
	{
		if(position.x<0)
		{
			//position.x=xmax-1;
			next_position.x=(float)xmax-2;
		}
		if(position.z<0)
		{
			//position.z=zmax-1;
			next_position.z=(float)zmax-2;
		}
		if(position.z>=zmax-1)
		{
			//position.z=(float)1.0f;
			next_position.z=(float)1.0f;
		}
		if(position.x>=xmax-1)
		{
			//position.x=(float)1.0f;
			next_position.x=(float)1.0f;
		}
	}

	//do all calculating of next and switch with cur pos based on collision detection
	void Animate( scalar_t deltaTime) {
	
			if(!collision)
			{
				position=next_position;
			}
			else
			{
				collision=false;
			}
			calculate_next(deltaTime);




			wheelclass_left_front->position = Vector(position.x, position.y, position.z);
			wheelclass_right_front->position = Vector(position.x, position.y, position.z);
			wheelclass_back->position = Vector(position.x, position.y, position.z);


	} // end Animate()


	/*
	 * AI Section
	 */

	//make the car go in the positive z direction
	void gopz()
	{
		car_turn_angle=0;
		inc_wheel_speed();
		last_dir = 0;
	}

	//make the car go in the negative z direction
	void gonz()
	{
		car_turn_angle=180;
		inc_wheel_speed();
		last_dir = 1;
	}
		
	//make car go in the positive x direction
	void gopx()
	{
		car_turn_angle=90;
		inc_wheel_speed();
		last_dir = 2;
	}

	//make car go in the negative x direction
	void gonx()
	{
		car_turn_angle=270;
		inc_wheel_speed();
		last_dir = 3;
	}


	//failed AI attmept 3, not used
	void AI2(bool** road_path,int xmax,int zmax) {
		int x=(int)floor(position.x);
		int z=(int)floor(position.z);

		if ( z >= zmax-2 ) {
			position.z = 0;
			return;
		}
		if ( z <= 0 ) {
			position.z = (float)zmax-1;
			return;
		}
		if ( x >= xmax-2 ) {
			position.x = 0;
			return;
		}
		if ( x <= 0 ) {
			position.x = (float)xmax-1;
			return;
		}


		bool one = road_path[z][x+1];
		bool two = road_path[z+1][x];
		bool three = road_path[z][x-1];
		bool four = road_path[z-1][x];


		if ( facing_dir == 1 ) {

		}
		else if ( facing_dir == 2 ) {
			inc_wheel_speed();

		}
		else if ( facing_dir == 3 ) {



		}
		else if ( facing_dir == 4 ) {




		}
	}


	//AI function that controlls computer cars
	void AI(bool** road_path,int xmax,int zmax) {

		//quasi successful AI attempt 4
		int x=(int)floor(position.x);
		int z=(int)floor(position.z);


		bool pz = false;
		bool nz = false;
		bool px = false;
		bool nx = false;

		if(x<0)
		{
			//stop_car();
			position.x=(float)xmax-2;
			next_position.x=(float)xmax-2;
			inc_wheel_speed();
			//gopx();
			//car_turn_angle+=180;
			//velocity=-velocity;
			return;
		}
		if(z<0)
		{
			//stop_car();
			position.z=91.5f;
			next_position.z=91.5f;
			inc_wheel_speed();
			//gopz();
			//car_turn_angle+=180;
			//velocity=-velocity;
			return;
		}
		if(z>=zmax-1)

		{
			//stop_car();
			position.z=(float)21.5f;
			next_position.z=(float)21.5f;
			inc_wheel_speed();
			return;
		}
		if(x>=xmax-1)
		{
		//	stop_car();
			position.x=(float)1.5f;
			next_position.x=(float)1.5f;
			inc_wheel_speed();
			//gonx();
			//car_turn_angle+=180;
			//velocity=-velocity;
			return;
		}

		if(z>=zmax)
		{
			pz=false;
		}
		else
		{
			pz=road_path[z+1][x];
		}
		if(z<=0)
		{
			nz=false;
		}
		else
		{
			nz=road_path[z-1][x];
		}

		if(x>=xmax)
		{
			px=false;
		}
		else
		{
			px=road_path[z][x+1];
		}
		if(x<=0)
		{
			nx=false;
		}
		else
		{
			nx=road_path[z][x-1];
		}

		int r=rand()%6;

		if(r==0)
		{
			//go pz
			if(pz)
				gopz();
			else if(px)
				gopx();
			else if(nx)
				gonx();
			else
				gonz();				
		}
		else if(r==1)
		{
			//go nz
			if(nz)
				gonz();
			else if(px)
				gopx();
			else if(nx)
				gonx();
			else
				gopz();
		}
		else if(r==2)
		{
			//go px
			if(px)
				gopx();
			else if(pz)
				gopz();
			else if(nz)
				gonz();
			else
				gonx();
		}
		else if (r==3 )
		{
			//go nx
			if(nx)
				gonx();
			else if(nz)
				gonz();
			else if(pz)
				gopz();
			else
				gopx();
		}
		else {
			if ( (last_dir == 0) && pz ) {
				gopz();
			}
			else if ( (last_dir == 1) && nz ) {
				gonz();
			}
			else if ( (last_dir == 2) && px ) {
				gopx();
			}
			else if ( (last_dir == 3) && nx ) {
				gonx();
			}
		}


		box->rotatebox( car_turn_angle, Vector(0.0f,0.0f,0.0f));
		//box->Draw();

		//failed AI attempt 2

		/*
		bool found_direction = false;


		if ( (z > 1) && (z < zmax-1) && (x > 1) && (x < xmax-1) ) {

			direction = 1.0f;

			if ( velocity.z < 0 ) {
				forward = road_path[z+1][x];
				left = road_path[z][x+1];
				right = road_path[z][x-1];
				backward = road_path[z-1][x];
			}
			else if (velocity.z > 0) {
				forward = road_path[z-1][x];
				left = road_path[z][x-1];
				right = road_path[z][x+1];
				backward = road_path[z+1][x];
			}
			else if ( velocity.x < 0 ) {
				forward = road_path[z][x+1];
				left = road_path[z-1][x];
				right = road_path[z+1][x];
				backward = road_path[z][x-1];
			}
			else if (velocity.x > 0) {
				forward = road_path[z][x-1];
				left = road_path[z+1][x];
				right = road_path[z-1][x];
				backward = road_path[z][x+1];
			}

			double random=0;
			srand(time(null));
			random = rand()%3;

			forward = true;
			left = true;

			if ( forward ) {
				if ( left && (random==1) ) {
					// turn left
					stop_car();
					car_turn_angle+=90.0f;
					inc_wheel_speed();
					inc_wheel_speed();
					inc_wheel_speed();
					inc_wheel_speed();
					inc_wheel_speed();
					inc_wheel_speed();
					inc_wheel_speed();			
				}
				else if ( right && (random==2)) {
					// turn right
					stop_car();
					car_turn_angle-=90.0f;
					inc_wheel_speed();
				}
				else {
					// just go forward
					inc_wheel_speed();

				}
			}
			else {
				if ( left && (random==1) ) {
					// turn left
					stop_car();
					car_turn_angle+=90.0f;
					inc_wheel_speed();
				}
				else if ( right && (random==2)) {
					// turn right
					stop_car();
					car_turn_angle-=90.0f;
					inc_wheel_speed();
				}
				else {
					// just go backwards
					stop_car();
					car_turn_angle-=180.0f;
					inc_wheel_speed();
				}
			}

		}
		else {
			stop_car();
		}*/


		//failed AI attempt 1


		//position=next_position;

//		int x=(int)floor(position.x);
	//	int z=(int)floor(position.z);
	//	bool forward,backward,left,right;
/*
		bool breakout=false;
		if(x<0||z<0||x>=xmax||z>=zmax)
		{
			
			if ( x < 0 ) {
				position.x = 1.0f;
			}
			if ( z < 0 ) {
				position.z = 1.0f;
			}
			if ( x >= xmax ) {
				position.x = xmax - 1.0f;
			}
			if ( z >= zmax ) {
				position.z = zmax - 1.0f;
			}

			stop_car();
			forward=false;
			backward=false;
			right=false;
			left=false;
			breakout=true;
		}
		else if(velocity.z==0)
		{
			if(velocity.x==0)
			{
				inc_wheel_speed();
			}
			else if(velocity.x<0)
			{
				if(x>0)
				{
					forward=road_path[z][x-1];
				}
				else
				{
					forward=false;
				}
				if(z>0)
				{
					right=road_path[z-1][x];
				}
				else
				{
					right=false;
				}
				if(z<zmax-1)
				{
					left=road_path[z+1][x];
				}
				else
				{
					left=false;
				}
				if(x<xmax-1)
				{
					backward=road_path[z][x+1];
				}
				else
				{
					backward=false;
				}
			}
			else
			{
				if(x<xmax-1)
				{
					forward=road_path[z][x+1];
				}
				else
				{
					forward=false;
				}
				if(z<zmax-1)
				{
					right=road_path[z+1][x];
				}
				else
				{
					right=false;
				}
				if(z>0)
				{
					left=road_path[z-1][x];
				}
				else
				{
					left=false;
				}
				if(x>0)
				{
					backward=road_path[z][x-1];
				}
				else
				{
					backward=false;
				}
			}
		}
		else if(velocity.z<0)
		{
			if(z>0)
			{
				forward=road_path[z-1][x];
			}
			else
			{
				forward=false;
			}
			if(x<xmax-1)
			{
				right=road_path[z][x+1];
			}
			else
			{
				right=false;
			}
			if(x>0)
			{
				left=road_path[z][x-1];
			}
			else
			{
				left=false;
			}
			if(z<zmax-1)
			{
				backward=road_path[z+1][x];
			}
			else
			{
				backward=false;
			}
		}
		else
		{
			if(z<zmax-1)
			{
				forward=road_path[z+1][x];
			}
			else
			{
				forward=false;
			}
			if(x>0)
			{
				right=road_path[z][x-1];
			}
			else
			{
				right=false;
			}
			if(x<xmax-1)
			{
				left=road_path[z][x+1];
			}
			else
			{
				left=false;
			}
			if(z>0)
			{
				backward=road_path[z-1][x];
			}
			else
			{
				backward=false;
			}
		}
		bool flag=false;

		double random=0;
		srand(time(null));

		fstream poses("posies.txt",ios::app);
		poses<<last_safe_x<<"\t"<<last_safe_z<<"\t"<<x<<"\t"<<z<<endl;
		if(!(last_safe_x==x&&last_safe_z==z))//||(!right&&!left&&!forward))
		{
			if(true)//forward==false)
			{
				while(!flag&&!breakout)
				{

					random = rand()%3+1;

					/*if(random==0)
					{
						if(forward)
						{
							poses<<"move forward"<<endl;
							inc_wheel_speed();
							flag=true;
						}
					}
					else //if(random==1)
					//{/*

						if(left)
						{
							poses<<"move left"<<endl;
							car_turn_angle+=90;
							stop_car();
							inc_wheel_speed();
							flag=true;
						}
					//}
						else if(forward)
						{
							inc_wheel_speed();
						}
					else if(random==2)
					{
						if(backward)
						{
							poses<<"move backward"<<endl;
							stop_car();
							car_turn_angle+=180;
							inc_wheel_speed();
							flag=true;
						}
					}
					else
					{
						if(right)
						{
							poses<<"move right"<<endl;
							car_turn_angle-=90;
							stop_car();
							inc_wheel_speed();
							flag=true;
						}
					}//else
				}//while
			}
			else
			{

				inc_wheel_speed();
			}
		}//if
		else
		{

			inc_wheel_speed();
		}
			if(right)
				poses<<"can right:";
			if(left)
				poses<<"can left:";
			if(backward)
				poses<<"can back:";
		poses.close();*/

		last_safe_x=x;
		last_safe_z=z;

		//Animate(1);


	}

	public:
		GLfloat gta_turn;
		GLfloat car_turn_angle;
		GLfloat delta_turn;
		GLfloat car_angle;
		GLfloat dca;
		bool do_skid;
		GLfloat MAX_TURN;
		GLfloat MIN_TURN;
		GLfloat MAX_A;
		GLfloat MAX_V;
		bool right;
		bool left;
		bool up;
		bool down;

		int facing_dir;

		GLfloat direction;
		Vector deceleration;
		int type;
		int orientation;
		Vector next_position;

		int last_safe_x;
		int last_safe_z;
		int last_dir;
		bool waypoint;
		bool changing_dir;
		bool check_collision;
		
		//int xmax,zmax;

	private:
		char *t;
		struct Skid{
			GLfloat x;
			GLfloat z;
			unsigned int timer;
			bool linked;
			Skid *next;
		};

		GLfloat last_elapsed;

		GLint entire_car;		// this car's display list

		GLfloat rotate_val;

		Skid *skid;
		Skid *skid_last;
		bool skid_link;


		GLfloat rock_val;

		// the three wheel objects this car has
		Wheel* wheelclass_left_front;
		Wheel* wheelclass_right_front;
		Wheel* wheelclass_back;


		bool collision;

		GLfloat last_angle;
		Vector last_velocity;
}; // end Car class
#endif