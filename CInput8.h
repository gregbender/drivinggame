// used for direct input
// source openGL Game Programming (ISBN# 0761533303)

#ifndef __CINPUT8_H__
#define __CINPUT8_H__

#include <windows.h>				// standard Windows app include
#include <dinput.h>

#define WIN32_LEAN_AND_MEAN				// trim the excess fat from Windows

typedef unsigned char UCHAR;

#define SafeRelease(x)	if (x) {x->Release(); x=NULL;}

bool Init_CInput8(HINSTANCE h);
bool Shutdown_CInput8(void);

bool Init_Keyboard(HWND hWnd);
bool Acquire_Keyboard();
bool Unacquire_Keyboard();
bool Read_Keyboard();
bool Release_Keyboard();
bool KeyDown(DWORD key);
bool KeyUp(DWORD key);
bool KeyPress(DWORD key);

bool Init_Mouse(HWND hWnd);
bool Acquire_Mouse(void);
bool Unacquire_Mouse(void);
bool Read_Mouse(void);
bool Release_Mouse(void);
void Get_Mouse_X(float &m_x);
void Get_Mouse_Y(float &m_y);
void Get_Mouse_Coords(float &m_x, float &m_y);
void Get_Movement(float &m_x, float &m_y);
bool Button_Down(int mouse_button);
bool Button_Up(int mouse_button);

// defines for mouse
#define LEFT_BUTTON			0
#define RIGHT_BUTTON		1
#define MIDDLE_BUTTON		2

#endif
