#pragma once

#include "Util/MeduzaUtil.h"

namespace meduza
{
	class Shader
	{
	public:
		Shader(unsigned int a_id)
		{
			m_id = a_id;
		}
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		inline void SetLayout(meduza::ShaderLayout a_layout) { m_shaderLayout = a_layout; }
		inline unsigned int GetId() const { return m_id; }
		inline meduza::ShaderLayout GetLayout() const { return m_shaderLayout; }

	protected:
		unsigned int m_id;
		meduza::ShaderLayout m_shaderLayout;
	};
}