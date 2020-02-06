#pragma once

struct Colour;
struct Drawable;

class Window;

class RenderLayer
{
public:
	virtual void Update(float) = 0;
	virtual void Frame() = 0;
	virtual void Clear(Colour) = 0; 
	virtual void DestroyLayer() = 0;
	virtual void Draw(Drawable) = 0;

	virtual bool IsWindowActive();
protected:
	virtual void CreateNewWindow(int,int,const char*) = 0;
	virtual void InitImGui();

	ImGuiIO m_io;
	Window* m_window = nullptr;

	std::vector<RenderItem*> m_renderItems;
};

