#pragma once
#include "../RenderLayer.h"

class Dx12_Device;
class Dx12_Swapchain;
class Dx12_Fence;
class Dx12_CommandQueue;
class Dx12_CommandList;
class Dx12_CommandAllocator;
class Dx12_Descriptor;

class Dx12_RenderLayer : public RenderLayer
{
public:
	Dx12_RenderLayer(int,int,const char*);
	~Dx12_RenderLayer();

public:
	virtual void Update(float) override;
	virtual void Frame() override;
	virtual void Clear(Colour) override;
	virtual void DestroyLayer() override;
	virtual void Draw(Drawable) override;

protected:
	virtual void CreateNewWindow(int, int, const char*) override;
	virtual void InitImGui();

private:
	void EnableDebugger();

private:
	Dx12_Device* m_device;
	Dx12_Swapchain* m_swapChain;
	Dx12_CommandQueue* m_cmdQueue;
	Dx12_CommandList* m_cmdList;

	Dx12_Descriptor* m_rtv;
	Dx12_Descriptor* m_srv;

};