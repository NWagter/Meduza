#pragma once

typedef const unsigned char keyCode;

namespace meduza
{
	namespace events
	{
		namespace keyCodes
		{
			keyCode g_keyCode_W = 87;
			keyCode g_keyCode_A = 65;
			keyCode g_keyCode_S = 83;
			keyCode g_keyCode_D = 68;
		}

		enum class Event
		{
			Unkown = 0,
			// == Window
			WindowResize,
		};
	}
}