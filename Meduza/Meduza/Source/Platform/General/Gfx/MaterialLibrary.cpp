#include "mePch.h"

#include "Core/Core.h"

#include "Platform/General/Gfx/MaterialLibrary.h"
#include "Platform/General/Resources/Shader.h"

#include "Platform/General/Utils/MeduzaHelper.h"

meduza::MaterialLibrary* meduza::MaterialLibrary::m_instance = nullptr;

meduza::MaterialLibrary::MaterialLibrary()
{
	if (m_instance != nullptr)
	{
		return;
	}
	m_instance = this;
}

meduza::MaterialLibrary::~MaterialLibrary()
{
	for (auto s : m_instance->m_materials)
	{
		auto shader = s.second;
		delete shader;
	}

	m_instance->m_materials.clear();
}

meduza::Material* meduza::MaterialLibrary::CreateMaterial(Shader& a_shader, std::string a_name)
{
	if (&a_shader == nullptr)
	{
		return nullptr;
	}

	unsigned int hashedId = utils::GetHashedID(a_name);

	if (m_instance->m_materials[hashedId] != nullptr)
	{
		ME_GFX_LOG("Material %s already exists! \n", a_name.c_str());
		return m_instance->m_materials[hashedId];
	}

	Material* newMaterial = new Material(a_shader);
	m_instance->m_materials[hashedId] = newMaterial;

	return newMaterial;
}

meduza::Material* meduza::MaterialLibrary::GetMaterial(unsigned int a_id)
{
	if (m_instance->m_materials[a_id] != nullptr)
	{
		return m_instance->m_materials[a_id];
	}
	
	ME_GFX_LOG("Material doesn't exists! \n");
	return nullptr;
}
