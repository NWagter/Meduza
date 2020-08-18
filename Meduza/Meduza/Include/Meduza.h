#pragma once

#include "Math/MeduzaMath.h"
#include "Util/MeduzaUtil.h"

namespace meduza
{
	class ImGuiRenderer;
	class Window;
	class ShaderLibrary;
	class MaterialLibrary;
	class TextureLibrary;
	class EventSystem;

	class Camera;

	class Scene;
	class Renderable;

	class Shader;
	class Material;
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

	namespace editor
	{
		class IEditor;
	}

	class Meduza 
	{
	public:
		Meduza(API);
		Meduza(API, std::string);
		~Meduza();

		API GetCurrentAPI() const;

// ============ Tools

		void EnableImGui();
		void ChangeApi(meduza::API);

// ============ Load Resource

		std::string LoadShader(std::string) const;
		Shader& GetShader(std::string) const;

		std::string LoadTexture(std::string) const;
		Texture& GetTexture(std::string) const;

// =========== Materials
		meduza::Material& CreateMaterial(Shader*, std::string = "New_Material");
		meduza::Material& GetMaterial(std::string);
		meduza::Material& GetMaterial(unsigned int);

		void SetMaterialParameter(meduza::Material&, std::string, float[]);
		void SetMaterialParameter(meduza::Material&, std::string, meduza::Texture&);
// ============ Camera

		void SetNewCamera(CameraPerspective, math::Vec2, math::Vec2 = {-1,1});
		void SetView(math::Vec2, math::Vec2 = { -1,1 });
		void SetCamEye(math::Vec3);
		void SetSolidColour(Colour);
		void SetSolidColour(float[4]);

// ============  Renderer

		void Submit(Renderable&);
		void Submit(Scene&);

		void Clear();

		void SwapBuffers();


		void Update(const float);
		void Peek();
		bool IsWindowActive() const;
		std::string GetWindowName() const;
		void SetWindowTitle(std::string);

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
		void SetupRenderer(meduza::API);
		void SetupRenderer(math::Vec2);

		renderer::Renderer* m_renderer = nullptr;
		ImGuiRenderer* m_imGuiRenderer = nullptr;
		ShaderLibrary* m_shaderLibrary = nullptr;
		MaterialLibrary* m_materialLibrary = nullptr;
		TextureLibrary* m_textureLibrary = nullptr;
		Window* m_window = nullptr;
		EventSystem* m_eventSystem = nullptr;
		Camera* m_camera = nullptr;
		editor::IEditor* m_editorMenu = nullptr;

		bool m_apiChange = false;
		bool m_reload = false;

	};
}