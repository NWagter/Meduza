#pragma once

namespace meduza
{
	enum class API
	{

	};


	class Meduza 
	{
	public:
		Meduza();
		~Meduza();



		void Clear(float[]);

		void Render();
		bool IsWindowActive() const { return m_windowActive; }

	private:
		bool m_windowActive = false;
	};
}