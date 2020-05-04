#pragma once

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

		inline unsigned int GetId() const { return m_id; }

	private:
		unsigned int m_id;
	};
}