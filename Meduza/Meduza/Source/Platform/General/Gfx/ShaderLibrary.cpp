#include "mePch.h"

#include "Core.h"

#include "Util/MeduzaHelper.h"

#include "Platform/General/Gfx/ShaderLibrary.h"
#include "Platform/General/Utils/ShaderUtils.h"

#ifdef WINDOWS

#include "Platform/Windows/Resources/OpenGL/ShaderGL.h"

#endif // WINDOWS

meduza::ShaderLibrary* meduza::ShaderLibrary::m_instance = nullptr;

meduza::ShaderLibrary::ShaderLibrary()
{
	if (m_instance != nullptr)
	{
		return;
	}

	m_instance = this;
}

meduza::ShaderLibrary::~ShaderLibrary()
{
	for (auto s : m_instance->m_shaders)
	{
		auto shader = s.second;
		delete shader;
	}

	m_instance->m_shaders.clear();
}

meduza::Shader* meduza::ShaderLibrary::LoadShader(std::string a_vertPath, std::string a_fragPath)
{
	switch (MeduzaHelper::ms_activeAPI)
	{
	case meduza::API::OpenGL:
	{

		utils::ShaderSources source = utils::ShaderUtils::GetSources(a_vertPath, a_fragPath);

		unsigned int hashedId = utils::ShaderUtils::GetHashedID(source.m_shaderName);

		//Check if already exists
		if (m_instance->m_shaders[hashedId] != nullptr)
		{
			return GetShader(hashedId);
		}

		m_instance->m_shaders[hashedId] = new ShaderGL(source);
		return GetShader(hashedId);
	}
#ifdef WINDOWS
	case meduza::API::DirectX12:
	{

		break;
	}
#endif // WINDOWS
	}

	return nullptr;
}

meduza::Shader* meduza::ShaderLibrary::LoadShader(std::string a_path)
{
	switch (MeduzaHelper::ms_activeAPI)
	{
	case meduza::API::OpenGL:
	{
		utils::ShaderSources source = utils::ShaderUtils::GetSources(a_path);
		unsigned int hashedId = utils::ShaderUtils::GetHashedID(source.m_shaderName);

		//Check if already exists
		if (m_instance->m_shaders[hashedId] != nullptr)
		{
			return GetShader(hashedId);
		}

		m_instance->m_shaders[hashedId] = new ShaderGL(source);

		ME_CORE_LOG("Loading of : %s was Succesfull! \n", a_path.c_str());
		return GetShader(hashedId);
	}
#ifdef WINDOWS
	case meduza::API::DirectX12:
	{

		break;
	}
#endif // WINDOWS

	}

	return nullptr;
}

meduza::Shader* meduza::ShaderLibrary::GetShader(std::string a_name)
{
	return GetShader(utils::ShaderUtils::GetHashedID(a_name));
}

meduza::Shader* meduza::ShaderLibrary::GetShader(unsigned int a_id)
{
	//Check if already exists
	if (m_instance->m_shaders[a_id] == nullptr)
	{
		return nullptr;
	}


	return m_instance->m_shaders[a_id];
}

bool meduza::ShaderLibrary::UnLoadShader(std::string a_name)
{
	//Check if already exists
	if (!UnLoadShader(utils::ShaderUtils::GetHashedID(a_name), false))
	{
		ME_CORE_LOG("Shader : %s doesn't exist", a_name.c_str());
		return false;
	}

	return true;
}

bool meduza::ShaderLibrary::UnLoadShader(unsigned int a_id, bool message)
{
	//Check if already exists
	if (m_instance->m_shaders[a_id] == nullptr)
	{
		if (message)
		{
			ME_CORE_LOG("Shader with ID : %i doesn't exist", a_id);
		}

		return false;
	}

	auto shader = m_instance->m_shaders[a_id];
	m_instance->m_shaders.erase(a_id);
	delete shader;

	return true;
}
