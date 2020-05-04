#pragma once

#include "Platform/General/Resources/Texture.h"

namespace meduza
{
	class TextureGL2D : public Texture2D
	{
	public:
		TextureGL2D(std::string);
		~TextureGL2D() override;

		unsigned int GetWidth() override { return m_width; }
		unsigned int GetHeight() override { return m_height; }

		void Bind(unsigned int a_slot = 0) override;
	private:
		unsigned int m_width = 0;
		unsigned int m_height = 0;
		unsigned int m_texture = 0;
	};
}