#pragma once

namespace mr 
{

	class Window;

	enum class RenderAPI
	{
		None = 0,
		DX12
	};

	class RenderLayer
	{
	public:
		static RenderLayer* CreateRenderLayer(Window&);
		virtual ~RenderLayer() {}
		static RenderAPI GetAPI();

		virtual void Clear(float[4]) = 0;
		virtual void PreRender() = 0;
		virtual void Render() = 0;
	};
}