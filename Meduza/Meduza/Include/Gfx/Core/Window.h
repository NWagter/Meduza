#pragma once


namespace meduza
{
	class Window
	{
	public:
		static Window* CreateNewWindow(int,int);
		virtual ~Window() = default;

		virtual void Peek() = 0;

		virtual void SetTitle(std::string) = 0;
		virtual std::string GetTitle() = 0;
		
		virtual bool WindowActive() = 0;

		virtual glm::vec2 GetSize() = 0;
	};
}