#pragma once

#include "Util/MeduzaUtil.h"

namespace meduza
{
	class Shader
	{
	public:
		Shader(unsigned int a_id, API a_api)
		{
			m_id = a_id;
			m_shaderAPI = a_api;
		}
		virtual ~Shader() = default;

		virtual void Reload() = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		inline void SetLayout(meduza::ShaderLayout a_layout) { m_shaderLayout = a_layout; }
		inline unsigned int GetId() const { return m_id; }
		inline meduza::ShaderLayout GetLayout() const { return m_shaderLayout; }
		inline API GetAPI() const { return m_shaderAPI; }

	protected:
		unsigned int m_id;
		meduza::ShaderLayout m_shaderLayout;
		API m_shaderAPI;
	};
}