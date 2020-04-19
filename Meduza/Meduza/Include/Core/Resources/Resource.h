#pragma once

namespace meduza
{
	class Resource
	{
	public:
		Resource(unsigned int);
		virtual ~Resource() = default;

		virtual void LoadResource(std::string) = 0;
		virtual void UnLoadResource() = 0;
		virtual void ReloadResource() = 0;

	protected:

		unsigned int m_resourceId;
		std::string m_filePath;
	};
}