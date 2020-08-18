#pragma once

typedef const unsigned char keyCode;

namespace meduza
{
	namespace events
	{
		namespace keyCodes
		{
			keyCode g_keyCode_0 = 0x30;
			keyCode g_keyCode_1 = 0x31;
			keyCode g_keyCode_2 = 0x32;
			keyCode g_keyCode_3 = 0x33;
			keyCode g_keyCode_4 = 0x34;
			keyCode g_keyCode_5 = 0x35;
			keyCode g_keyCode_6 = 0x36;
			keyCode g_keyCode_7 = 0x37;
			keyCode g_keyCode_8 = 0x38;
			keyCode g_keyCode_9 = 0x39;

			keyCode g_keyCode_A = 0x41;
			keyCode g_keyCode_C = 0x43;
			keyCode g_keyCode_B = 0x42;
			keyCode g_keyCode_D = 0x44;
			keyCode g_keyCode_E = 0x45;
			keyCode g_keyCode_F = 0x46;
			keyCode g_keyCode_G = 0x47;
			keyCode g_keyCode_H = 0x48;
			keyCode g_keyCode_I = 0x49;
			keyCode g_keyCode_J = 0x4A;
			keyCode g_keyCode_K = 0x4B;
			keyCode g_keyCode_L = 0x4C;
			keyCode g_keyCode_M = 0x4D;
			keyCode g_keyCode_N = 0x4E;
			keyCode g_keyCode_O = 0x4F;
			keyCode g_keyCode_P = 0x50;
			keyCode g_keyCode_Q = 0x51;
			keyCode g_keyCode_R = 0x52;
			keyCode g_keyCode_S = 0x53;
			keyCode g_keyCode_T = 0x54;
			keyCode g_keyCode_U = 0x55;
			keyCode g_keyCode_V = 0x56;
			keyCode g_keyCode_W = 0x57;
			keyCode g_keyCode_X = 0x58;
			keyCode g_keyCode_Y = 0x59;
			keyCode g_keyCode_Z = 0x5A;
		}

		enum class Event
		{
			Unkown = 0,
			// == Window
			WindowResize,
		};
	}
}