#pragma once

#include "Platform/General/Resources/Texture.h"

namespace meduza
{
	class Texture2DGL : public Texture2D
	{
	public:
		Texture2DGL(std::string, unsigned int = 0);
		~Texture2DGL() override;

		unsigned int GetWidth() override { return m_width; }
		unsigned int GetHeight() override { return m_height; }
		unsigned int GetId() const override { return m_textureId; }

		void Bind(unsigned int a_slot = 0) override;
	private:
		unsigned int m_width = 0;
		unsigned int m_height = 0;
		unsigned int m_texture = 0;
		unsigned int m_textureId = 0;
	};
}