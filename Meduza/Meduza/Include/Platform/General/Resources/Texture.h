#pragma once

namespace meduza
{
	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;
		virtual unsigned int GetId() const = 0;

		virtual void Bind(unsigned int a_slot = 0) = 0;
	};

	class Texture2D : public Texture
	{
	public :
		static Texture2D* Create(std::string, unsigned int = 0);
	};
}