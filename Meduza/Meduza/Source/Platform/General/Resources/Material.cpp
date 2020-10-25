#include "mePch.h"

#include "Platform/General/Resources/Material.h"
#include "Platform/General/Resources/Shader.h"
meduza::Material::Material(Shader& a_shader)
{
	SetShader(a_shader);
	float c[] = { 1,0,1,1 };
	SetData("a_colour", c);
}

meduza::Material::~Material()
{
}

unsigned int meduza::Material::GetShaderID()
{
	return m_shader->GetId();
}

void meduza::Material::SetShader(Shader& a_shader)
{
	m_shader = &a_shader;
	ScaleBuffer();
}

void meduza::Material::SetData(std::string a_name, float a_data[])
{
	int index = 0;
	int size = 0;
	for (auto i : m_shader->GetLayout().m_layout)
	{
		if (i.second == a_name)
		{
			size = i.first;
			break;
		}
		index += i.first;
	}

	for (int i = 0; i < size; i++)
	{
		m_buffer[index + i] = a_data[i];
	}
}

void meduza::Material::SetData(std::string a_name, unsigned int a_data[])
{
	int index = 0;
	int size = 0;
	for (auto i : m_shader->GetLayout().m_layout)
	{
		if (i.second == a_name)
		{
			size = i.first;
			break;
		}
		index += i.first;
	}

	for (int i = 0; i < size; i++)
	{
		m_buffer[index + i] = float(a_data[i]);
	}
}

std::vector<float> meduza::Material::GetData(std::string a_name)
{
	std::vector<float> data;

	int index = 0;
	int size = 0;

	for (auto i : m_shader->GetLayout().m_layout)
	{
		if (i.second == a_name)
		{
			size = i.first;
			break;
		}
		index += i.first;
	}

	for (int i = 0; i < size; i++)
	{
		data.push_back(m_buffer[index + i]);
	}

	return data;
}

void meduza::Material::Reload()
{
}

void meduza::Material::Unload()
{
}

void meduza::Material::ScaleBuffer()
{
	unsigned int scale = 0;
	for (auto i : m_shader->GetLayout().m_layout)
	{
		scale += i.first;
	}
	m_buffer.resize(scale);
}
