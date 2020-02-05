#pragma once

class RenderLayer;

enum class GfxAPI;

struct Colour;
struct Drawable;

class Meduza
{
public:
	Meduza(GfxAPI);
	~Meduza();

	static void Update(float);
	static void Frame();
	static void Clear(Colour a_clear);

	static void Draw(Drawable);
	static void ChangeAPI(GfxAPI);

	static void Destroy();
	static bool IsActive();
private:
	Colour m_colour;
	static Meduza* m_instance;
	RenderLayer* m_renderLayer = nullptr;

	GfxAPI m_api;
	bool m_RendererActive;

	void Initilize();
};

