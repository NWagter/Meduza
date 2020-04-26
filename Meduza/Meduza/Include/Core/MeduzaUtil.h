#pragma once

// Use (void) to silent unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

namespace meduza
{
	enum class API
	{
		OpenGL = 0,
#ifdef WINDOWS
		DirectX12,
#endif // WIN

#ifdef LINUX
		ES2,
#endif

	};

	struct Colour
	{
		Colour() = default;
		Colour(float a_r, float a_g , float a_b, float a_a)
		{
			m_r = a_r;
			m_g = a_g;
			m_b = a_b;
			m_a = a_a;
		}
		Colour(float a_colour[4])
		{
			m_r = a_colour[0];
			m_g = a_colour[1];
			m_b = a_colour[2];
			m_a = a_colour[3];
		}

#pragma warning(push)
#pragma warning(disable : 4201)
		union {
			struct
			{
				float m_r;
				float m_g;
				float m_b;
				float m_a;
			};
			float m_colour[4];
		};
#pragma warning(pop)
	};

	namespace Colours
	{
		static const Colour RED = Colour(1.0f, 0, 0, 1.0f);
		static const Colour BLUE = Colour(0, 0, 1.0f, 1.0f);
		static const Colour GREEN = Colour(0, 1.0f, 0, 1.0f);
		static const Colour MAGENTA = Colour(0, 1.0f, 0, 1.0f);
		static const Colour ROYAL_PURPLE = Colour(0.47f, 0.32f, 0.66f, 1.0f);
		static const Colour CELESTIAL_BLUE = Colour(0.29f, 0.59f, 0.82f, 1.0f);
	}

	struct Material
	{
		unsigned int m_shaderId = 0;
		unsigned int m_textureld = 0;

		float m_albedo[4] = { 1,1,1,1 };

	};

	class MeduzaHelper
	{
	public:

	};
}
