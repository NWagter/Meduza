#pragma once

namespace meduza
{
	namespace renderer
	{
		class Renderer;
	}

	class ImGuiRenderer
	{
	public:
		static ImGuiRenderer* CreateRenderer(renderer::Renderer&);

		virtual ~ImGuiRenderer() = default;

		virtual void Clear() = 0;
		virtual void Render() = 0;
	};
}