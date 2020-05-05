#pragma once

#include "Platform/General/Utils/ShaderUtils.h"

namespace meduza
{
	namespace utils
	{

		class ShaderDataGl : public ShaderData
		{
		public:
			void SetInt(const Shader&, std::string, int) override;
			void SetFloat(const Shader&, std::string, float) override;
			void SetFloat2(const Shader&, std::string, float[2]) override;
			void SetFloat3(const Shader&, std::string, float[3]) override;
			void SetFloat4(const Shader&, std::string, float[4]) override;
		};																
	}
}