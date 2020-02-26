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

enum class MeshType {
	Triangle = 0,
	Quad,
};

struct Colour {
	float r, g, b, a;
};

struct Drawable {

	MeshType meshType;
	DrawableType type;
	Colour colour;
	std::string textureLoc;
	int shaderId = 0;

	float posX = 0;
	float posY = 0;
};