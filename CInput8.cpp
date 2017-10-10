// used for direct input
// source openGL Game Programming (ISBN# 0761533303)

#include "CInput8.h"

LPDIRECTINPUT lpdi;
LPDIRECTINPUTDEVICE m_keyboard;
UCHAR keystate[256];
UCHAR keypress_state[256];

LPDIRECTINPUTDEVICE m_mouse = NULL;
float mX = 0.0f, mY = 0.0f, mZ = 0.0f;
DIMOUSESTATE mouse_state;

// Initiates input system
bool Init_CInput8(HINSTANCE h)
{

	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&lpdi, NULL)))
		return false;

	for (int i = 0; i < 256; i++)
		keypress_state[i] = 0;

	return true;
}


bool Init_Keyboard(HWND hWnd)
{
	if (FAILED(lpdi->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL)))
		return false;
	if (FAILED(m_keyboard->SetDataFormat(&c_dfDIKeyboard)))
		return false;
	if (FAILED(m_keyboard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND |
		DISCL_NONEXCLUSIVE)))
		return false;
	if (FAILED(m_keyboard->Acquire()))
		return false;
	return true;
}

bool Acquire_Keyboard()
{
	if (FAILED(m_keyboard->Acquire()))
		return false;
	return true;
}

bool Unacquire_Keyboard()
{
	if (FAILED(m_keyboard->Unacquire()))
		return false;
	return true;
}

bool Read_Keyboard()
{
	if (FAILED(m_keyboard->GetDeviceState(sizeof(UCHAR[256]), (LPVOID)keystate)))
		return false;
	return true;
}

bool Release_Keyboard()
{
	SafeRelease(m_keyboard);
	return true;
}

bool KeyDown(DWORD key)
{
	return ((keystate[key] & 0x80) ? true : false);
}

bool KeyUp(DWORD key)
{
	return ((keystate[key] & 0x80) ? false : true);
}

bool KeyPress(DWORD key)
{
	if (KeyDown(key))
		keypress_state[key] = 1;

	if (keypress_state[key] == 1)
		if (KeyUp(key))
			keypress_state[key] = 2;

	if (keypress_state[key] == 2)
	{
		keypress_state[key] = 0;
		return true;
	}

	return false;
}

bool Init_Mouse(HWND hWnd)
{
	if (FAILED(lpdi->CreateDevice(GUID_SysMouse, &m_mouse, NULL)))
		return false;
	if (FAILED(m_mouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND |
		DISCL_NONEXCLUSIVE)))
		return false;
	if (FAILED(m_mouse->SetDataFormat(&c_dfDIMouse)))
		return false;
	if (FAILED(m_mouse->Acquire()))
		return false;
	return true;
}

bool Acquire_Mouse(void)
{
	if (FAILED(m_mouse->Acquire()))
		return false;
	return true;
}

bool Unacquire_Mouse(void)
{
	if (FAILED(m_mouse->Unacquire()))
		return false;
	return true;
}

bool Read_Mouse(void)
{
	if (FAILED(m_mouse->GetDeviceState(sizeof(DIMOUSESTATE),
		(LPVOID)&mouse_state)))
		return false;
	return true;
}

void Get_Movement(float &m_x, float &m_y)
{
	m_x = mouse_state.lX;
	m_y = mouse_state.lY;
}

void Get_Wheel_Movement(float &m_z)
{
	m_z = mouse_state.lZ;
}

void Get_Mouse_Coords(float &m_x, float &m_y)
{
	Get_Mouse_X(m_x);
	Get_Mouse_Y(m_y);
}

void Get_Mouse_X(float &m_x)
{
	mX += mouse_state.lX;
	if (mX < 0)
		mX = 0;

	m_x = mX;
}

void Get_Mouse_Y(float &m_y)
{
	mY += mouse_state.lY;
	if (mY < 0)
		mY = 0;

	m_y = mY;
}

bool Button_Down(int mouse_button)
{
	return ((mouse_state.rgbButtons[mouse_button] & 0x80) ? true : false);
}

bool Button_Up(int mouse_button)
{
	return ((mouse_state.rgbButtons[mouse_button] & 0x80) ? false : true);
}

bool Release_Mouse()
{
	if (Unacquire_Mouse())
		return false;
	SafeRelease(m_mouse);
	return true;
}

// shutdown input system
bool Shutdown_CInput8(void)
{
	SafeRelease(lpdi);
	return true;
}