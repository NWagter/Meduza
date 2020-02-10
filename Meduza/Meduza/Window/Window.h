#pragma once

class Window {
	
public:
	Window(int a_width, int a_height, std::string a_title);
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	virtual void SetTitle(const std::string a_newTitle);


	virtual bool PeekMsg() = 0;
	virtual bool IsWindowActive();
protected:
	int m_width;
	int m_height;
	std::string m_title;
	bool m_windowIsActive;
};