#pragma once

namespace meduza
{

	class Shader;
	class Texture;

	class Material
	{
	public:
		Material(Shader&);
		~Material();

		unsigned int GetShaderID();
		void SetShader(Shader&);
		void SetData(std::string, float[]);
		void SetData(std::string, unsigned int[]);
		std::vector<float> GetData(std::string);

	private:
		void ScaleBuffer();

		meduza::Shader* m_shader;
		bool m_instanced = false;
		std::vector<float> m_buffer;
	};
}
