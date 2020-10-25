#pragma once

#include "Platform/General/Gfx/ImGuiRenderer.h"

namespace meduza
{

	namespace renderer
	{
		class RendererDx12;
		class DescriptorDx12;
	}

	class ImGuiRendererDx12 : public ImGuiRenderer
	{
	public:
		ImGuiRendererDx12(renderer::Renderer&);
		~ImGuiRendererDx12() override;

		void Clear() override;
		virtual void Render() override;

	private:

		renderer::RendererDx12* m_renderer;
		renderer::DescriptorDx12* m_GuiHeap;
	};
}