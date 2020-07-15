#pragma once

#include "Platform/General/Resources/Texture.h"

namespace meduza
{
	class TextureLibrary
	{
	public:
		TextureLibrary();
		~TextureLibrary();

		static Texture* LoadTexture(std::string);

		static Texture* GetTexture(std::string);
		static Texture* GetTexture(unsigned int);

		static bool UnLoadTexture(std::string);
		static bool UnLoadTexture(unsigned int, bool = true);

		void Reload();
	private:
		static TextureLibrary* m_instance;
		std::unordered_map<unsigned int, Texture*> m_textures;
	};
}