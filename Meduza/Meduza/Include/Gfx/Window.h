#pragma once


namespace mr {

	enum class RenderAPI;

	class Window {

	public:
		static Window* NewWindow(int,int,RenderAPI);
		virtual ~Window() {}
		virtual void SetTitle(const std::string) = 0;
		virtual bool Peek() = 0;
		virtual void Resize() = 0; // give new size
		inline bool IsActive() { return m_isActive; }

	protected:
		bool m_isActive;
	};
}