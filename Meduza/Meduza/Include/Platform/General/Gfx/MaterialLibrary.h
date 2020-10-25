#pragma once

#include "Platform/General/Resources/Material.h"

namespace meduza
{
	class Shader;

	class MaterialLibrary
	{
	public:
		MaterialLibrary();
		~MaterialLibrary();

		static meduza::Material* CreateMaterial(Shader&, std::string);
		static meduza::Material* GetMaterial(unsigned int);

		void Reload();
	private:
		static MaterialLibrary* m_instance;
		std::unordered_map<unsigned int, Material*> m_materials;
	};

}