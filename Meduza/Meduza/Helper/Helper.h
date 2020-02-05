#pragma once
#include <string>

enum class GfxAPI
{
	DirectX12 = 0,
	Vulkan
};

enum class DrawableType {

	Sprite = 0,
	Model,
	Text
};

struct Colour {
	float r, g, b, a;
};

struct Drawable {

	DrawableType type;
	Colour colour;
	std::string textureLoc;
};