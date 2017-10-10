/* ---------------------------------------------------------------------------
** This is a wheel object. These are attatched to the car
**
** car.cpp
**
** Authors: Greg Bender
**          Michael Krauklis
** -------------------------------------------------------------------------*/
#ifndef __WHEEL_C_INCLUDED__
#define __WHEEL_C_INCLUDED__

// standard includes
#include "object.h"

/*
* Wheel object, represents a wheel of a car in 3D world
*/
class Wheel :public Object {
	public :

		/*
		* Car constructor
		*/
		Wheel() {
			position = Vector(0.0f, 0.0f, 0.0f);
			velocity = Vector(0.0f, 0.0f, 0.0f);
			acceleration = Vector(0.0f, 0.0f, 0.0f);

			scale = Vector(0.0f, 0.0f, 0.0f);
			translate = Vector( 0.0f, 0.0f, 0.0f);

			display_list = 0;

			wheel_angle = 0.0f;
			wheel_speed = 0.0f;
			wheel_speed_delta = 0.0f;

			// how much a car can speed up
			speed_change = 0.005f;
			angle_change = 1.0f;

			// how far a tire can turn
			turning_radius = 20.0f;
		} // end Car()

		/*
		* Car deconstructor, deletes the display lists
		*/

		~Wheel() {
			glDeleteLists(display_list, 1);
		} // end ~Car()

		void set_scale( Vector vec ) {
			scale = vec;
		}

		void set_translate ( Vector vec ) {
			translate = vec;
		}

		/*
		* Called from main to set what this cars display lists will represent
		*/
		void set_display_lists(GLint the_display_list) {
			display_list = the_display_list;
		}  // end set_display_lists()


		void dec_wheel_angle() {

			wheel_angle = wheel_angle - angle_change;

			if ( wheel_angle > 50.0f ) {
				wheel_angle = 50.0f;
			}
			if ( wheel_angle < -50.0f ) {
				wheel_angle = -50.0f;
			}

		}

		void inc_wheel_angle() {

			wheel_angle = wheel_angle + angle_change;

			if ( wheel_angle > turning_radius ) {
				wheel_angle = turning_radius;
			}

			if ( wheel_angle < -turning_radius ) {
				wheel_angle = -turning_radius;
			}

		}

		void dec_wheel_speed() {
			wheel_speed_delta = wheel_speed_delta - speed_change;

			acceleration += Vector(0.0f, 0.0f, -0.1f);
		}
		void inc_wheel_speed() {
			wheel_speed_delta = wheel_speed_delta + speed_change;

			acceleration += Vector(0.0f, 0.0f, 0.1f);
		}

		void do_wheel_rotation() {
				glRotatef( wheel_angle, 0.0f, 1.0f, 0.0f);
				glRotatef( wheel_speed, 1.0f, 0.0f, 0.0f);
		}

		void Draw() {
			glPushMatrix();

			//	glTranslatef( position.x, position.y, position.z);
				glTranslatef( translate.x, translate.y, translate.z );
				do_wheel_rotation();
			//	glScalef( scale.x, scale.y, scale.z );


				glCallList(display_list);
			glPopMatrix();
		}

		void reset_angle() {
			wheel_angle = 0.0f;
		}

		void Animate( scalar_t deltaTime) {
			wheel_speed = wheel_speed + wheel_speed_delta;


			float fastestTime = deltaTime;
		
			if (velocity.Length() > 0.0f) {
				acceleration += ((-velocity) * 0.00005f);
			}

			position += velocity * fastestTime + 
							acceleration * (fastestTime * fastestTime * 0.5f);
			velocity += acceleration * fastestTime;
		}

	public:
		GLfloat wheel_angle;	// current wheel angel
	private:
		
		GLint	display_list;	// this wheels display list


		GLfloat wheel_speed_delta;	// current change in wheel speed
		GLfloat wheel_speed;	// current wheel speed

		GLfloat speed_change;	// how fast a wheels speed changes
		GLfloat angle_change;	// how fast a cars angel changes
		GLfloat turning_radius;	// how far wheel can turn left or right


		Vector scale;
		Vector translate;
}; // end Wheel class
#endif
