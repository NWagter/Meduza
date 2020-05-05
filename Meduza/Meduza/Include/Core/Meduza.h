#pragma once

#include "Drawable/Sprite.h"
#include "MeduzaUtil.h"

#include<vector>
#include <string>

namespace meduza
{
	class ImGuiRenderer;
	class Window;
	class ShaderLibrary;
	class TextureLibrary;
	struct Colour;

	namespace renderer
	{
		class Renderer;
	}

	class Meduza 
	{
	public:
		Meduza(API);
		~Meduza();

// ============ Tools

		void EnableImGui();

// ============ Load Resource

		std::string LoadShader(std::string);
		std::string LoadTexture(std::string);

// ============  Renderer

		void Submit(drawable::Drawable*);
		void Submit(std::vector<drawable::Drawable*>);

		void Clear(float a_colour[4])
		{
			Colour c = Colour(a_colour);
			Clear(c);
		}
		void Clear(Colour);

		void SwapBuffers();


		void Peek();
		bool IsWindowActive() const;
		std::string GetWindowName();

		inline renderer::Renderer& GetGfx()
		{
			if (m_renderer != nullptr)
			{
				return *m_renderer;
			}

			static_assert(1, "NO RENDERER AVAILABLE");

			return *m_renderer;
		}

	private:
		renderer::Renderer* m_renderer = nullptr;
		ImGuiRenderer* m_imGuiRenderer = nullptr;
		ShaderLibrary* m_shaderLibrary = nullptr;
		TextureLibrary* m_textureLibrary = nullptr;
		Window* m_window = nullptr;
	};
}