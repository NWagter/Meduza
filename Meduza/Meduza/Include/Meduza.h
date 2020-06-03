#pragma once

#include "Math/MeduzaMath.h"
#include "Util/MeduzaUtil.h"

namespace meduza
{
	class ImGuiRenderer;
	class Window;
	class ShaderLibrary;
	class TextureLibrary;
	class EventSystem;

	class Camera;

	class Shader;
	class Texture;

	struct Colour;

	namespace drawable
	{
		class Drawable;
	}

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

// ============ Profile
		void DebugDrawStats(const float, bool = false);

// ============ Load Resource

		std::string LoadShader(std::string) const;
		Shader& GetShader(std::string) const;

		std::string LoadTexture(std::string) const;
		Texture& GetTexture(std::string) const;

// ============ Camera

		void SetNewCamera(CameraPerspective, math::Vec2, math::Vec2 = {-1,1});
		void SetView(math::Vec2, math::Vec2 = { -1,1 });
		void SetCamEye(math::Vec3);

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
		std::string GetWindowName() const;

		inline renderer::Renderer& GetGfx() const
		{
			if (m_renderer != nullptr)
			{
				return *m_renderer;
			}

			static_assert(1, "NO RENDERER AVAILABLE");

			return *m_renderer;
		}
		math::Vec2 GetWindowSize() const;
	private:
		renderer::Renderer* m_renderer = nullptr;
		ImGuiRenderer* m_imGuiRenderer = nullptr;
		ShaderLibrary* m_shaderLibrary = nullptr;
		TextureLibrary* m_textureLibrary = nullptr;
		Window* m_window = nullptr;
		EventSystem* m_eventSystem = nullptr;
		Camera* m_camera = nullptr;
	};
}