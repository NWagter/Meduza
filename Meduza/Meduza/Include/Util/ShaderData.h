#pragma once


struct ShaderData
{
	unsigned int m_id;
};

struct ShaderDataGL : public ShaderData
{
	unsigned int m_shaderProgram;
};