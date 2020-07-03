#pragma once

#include <vector>
#include <string>

namespace meduza
{
	enum class API
	{
		OpenGL = 0,
#ifdef WINDOWS
		DirectX12 = 1,
#endif // WIN

#ifdef LINUX
		ES2,
#endif

	};

	enum class CameraPerspective
	{
		Orthographic = 0,
		Perspective
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

	enum class Attributes
	{
		floatAttribute,
		vec2Attribute,
		vec3Attribute,
		vec4Attribute
	};

	struct VertexAttributes
	{
		void AddAttribute(Attributes a_att)
		{
			unsigned int offset = 0;;

			switch (a_att)
			{
			case Attributes::floatAttribute:
				offset = 1;
					break;
			case Attributes::vec2Attribute:
				offset = 2;
				break;
			case Attributes::vec3Attribute:
				offset = 3;
				break;
			case Attributes::vec4Attribute:
				offset = 4;
				break;
			}

			m_stride += offset * sizeof(float);
			m_layout.push_back(std::pair<Attributes,int>(a_att, offset));
		}

		unsigned int GetStride() const { return m_stride; }
		std::vector<std::pair<Attributes, int>> GetAttributes() const { return m_layout; }
	private:
		unsigned int m_stride = 0;
		std::vector<std::pair<Attributes, int>> m_layout;
	};

	enum class ShaderLayoutItem
	{
		itemFloat = 0,
		itemFloat2,
		itemFloat3,
		itemFloat4
	};

	struct ShaderLayout
	{
		void AddItem(ShaderLayoutItem a_item, std::string a_name)
		{
			unsigned int scale = 0;

			switch (a_item)
			{
			case meduza::ShaderLayoutItem::itemFloat:
				scale = 1;
				break;
			case meduza::ShaderLayoutItem::itemFloat2:
				scale = 2;
				break;
			case meduza::ShaderLayoutItem::itemFloat3:
				scale = 3;
				break;
			case meduza::ShaderLayoutItem::itemFloat4:
				scale = 4;
				break;
			}

			m_layout.push_back(std::pair<unsigned int, std::string>(scale, a_name));
		}

		std::vector<std::pair<unsigned int, std::string>> m_layout;
	};
}