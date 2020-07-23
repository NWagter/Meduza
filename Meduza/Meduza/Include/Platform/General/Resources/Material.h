#pragma once

namespace meduza
{

	class Shader;
	class Texture;

	class Material
	{
	public:
		Material() = default;
		Material(Shader&);
		~Material();

		unsigned int GetShaderID();
		void SetShader(Shader&);
		void SetData(std::string, float[]);
		void SetData(std::string, unsigned int[]);
		std::vector<float> GetData(std::string);

		void Reload();
	private:
		void ScaleBuffer();

		meduza::Shader* m_shader;
		bool m_instanced = false;
		std::vector<float> m_buffer;
	};
}
