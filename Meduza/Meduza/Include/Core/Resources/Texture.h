#pragma once

#include "Resource.h"

namespace meduza
{
	class Texture : Resource
	{
	public :
		Texture(unsigned int);
		~Texture() override;

		void LoadResource(std::string) override;
		void UnLoadResource() override;
		void ReloadResource() override;
	};
}