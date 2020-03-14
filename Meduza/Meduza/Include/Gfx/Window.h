#pragma once

namespace cr {

	enum class RenderAPI;

	class Window {

	public:
		static Window* CreateNewWindow(RenderAPI, int, int);
		virtual ~Window() {}
		virtual void SetTitle(const std::string) = 0;
		virtual bool Peak() = 0;
		virtual void Resize() = 0; // give new size
		inline bool IsActive() { return m_isActive; }
		inline glm::vec2 GetSize() { return m_size; }

	protected:
		bool m_isActive;
		glm::vec2 m_size;
	};
}