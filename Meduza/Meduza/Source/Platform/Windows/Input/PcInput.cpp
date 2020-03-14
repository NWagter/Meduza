#include "cepch.h"
#include "Core/Input/InputManager.h"
#include "Core/Input/KeyEnums.h"

void InputManager::Init() {
	FindController();
}

void InputManager::Update()
{
	//Tnx Katy hope you are still alive
	if (XInputGetState(m_controllerId, &m_controllerState) != ERROR_SUCCESS) {
		FindController();
		return;
	}
	//Checking of the buttons on the controller
	for (int i = 0; i < 16; i++)
	{
		if ((m_controllerState.Gamepad.wButtons & (1 << i)) != 0) {
			if (!IsKeyDown(256 + i)) {
				//Adding 265 to it so it doesn't mess up the keyboard controls
				OnButtonChange(256 + i, true);
			}
		}
		else if (IsKeyDown(256 + i)) {
			OnButtonChange(256 + i, false);
		}
	}
	//Checking of the two back triggers of the controllers
	float leftBackTrigger = (float)m_controllerState.Gamepad.bLeftTrigger / 255;
	if (m_joystick.m_joystickValues[JoystickAxis::Joystick_L2] != leftBackTrigger) {
		OnJoystickAxisChange(false, leftBackTrigger);
	}
	float rightBackTrigger = (float)m_controllerState.Gamepad.bRightTrigger / 255;
	if (m_joystick.m_joystickValues[JoystickAxis::Joystick_R2] != rightBackTrigger) {
		OnJoystickAxisChange(true, leftBackTrigger);
	}

	//Checking the position of the two thumbsticks
	float normLX = fmaxf(-1, (float)m_controllerState.Gamepad.sThumbLX / 32767);
	float normLY = fmaxf(-1, (float)m_controllerState.Gamepad.sThumbLY / 32767);

	normLX = (abs(normLX) < m_joystick.m_deadZone ? 0 : normLX);
	normLY = (abs(normLY) < m_joystick.m_deadZone ? 0 : normLY);

	if (m_joystick.m_joystickValues[JoystickAxis::Joystick_LThumb_Horizontal] != normLX || m_joystick.m_joystickValues[JoystickAxis::Joystick_LThumb_Vertical] != normLY) {
		OnThumbstickChange(false, normLX, normLY);
	}

	float normRX = fmaxf(-1, (float)m_controllerState.Gamepad.sThumbRX / 32767);
	float normRY = fmaxf(-1, (float)m_controllerState.Gamepad.sThumbRY / 32767);

	normRX = (abs(normRX) < m_joystick.m_deadZone ? 0 : normRX);
	normRY = (abs(normRY) < m_joystick.m_deadZone ? 0 : normRY);

	if (m_joystick.m_joystickValues[JoystickAxis::Joystick_RThumb_Horizontal] != normRX || m_joystick.m_joystickValues[JoystickAxis::Joystick_RThumb_Vertical] != normRY) {
		OnThumbstickChange(true, normRX, normRY);
	}
}

bool InputManager::FindController()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&m_controllerState, sizeof(XINPUT_STATE));

		if (XInputGetState(i, &m_controllerState) == ERROR_SUCCESS) {
			m_controllerId = i;
			return true;
		}
	}
	return false;
}