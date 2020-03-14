#pragma once
#include "Utils/IService.h"
#include "GFXHelper.h"

#include <memory>

namespace cr { class IDrawable; }

namespace ce { class Camera; }

namespace cr { class Window; }
namespace cr { class RenderLayer; }

namespace ce
{
	class RenderService :
		public IService
	{
	public:
		RenderService() = default;
		virtual ~RenderService() = default;

		void OnCreate() override;
		void OnDestroy() override;

		void Clear(float a_colour[4]);
		void Peak();
		void Update(float a_deltaTime);
		void Render();
		void Draw(cr::IDrawable* a_drawable);


		bool IsWindowActive();
		glm::vec2 GetSize();
		cr::RenderLayer* GetRenderLayer();

	protected:
		
	private:
		cr::Window* m_window = nullptr;
		cr::RenderLayer* m_renderer = nullptr;
		Camera* m_camera = nullptr;
	};
}