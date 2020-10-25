#pragma once
#include "Platform/General/ContextBase.h"

namespace Me
{
  namespace Renderer
  {
    namespace Dx12
    {
      class Device;
      class Descriptor;
      class CommandQueue;
      class CommandList;

      class Context : public ContextBase
      {
      public:
        Context(HWND, Device*);
        ~Context();
        
        void SwapBuffers(CommandList&);
        void Resize(float,float) override;

        void CreateSwapchain();
        void SetQueue(CommandQueue&);
        inline Microsoft::WRL::ComPtr<IDXGISwapChain4> GetSwapChain() { return m_swapChain; }
        inline ID3D12Resource* GetCurrentBuffer() { return m_frameBuffer[m_currentframeBufferIndex].Get(); }
        inline Microsoft::WRL::ComPtr<ID3D12Resource> GetBuffers(int a_id) { return m_frameBuffer[a_id]; }

			  inline CommandQueue* GetQueue() { return m_queue; }

        void ClearRTV();
        void CreateRTV(Descriptor&);
        void Resize(int, int);

        inline DXGI_FORMAT GetFormat() { return m_backBufferFormat; }
        inline HWND GetHWND() const { return m_hwnd; }
        inline unsigned int GetCurrentFrameIndex() const { return m_currentframeBufferIndex; }

        float m_width, m_height;
      private:
        bool m_resize = false;
        void CreateSwapChain();
        Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapChain;
        Microsoft::WRL::ComPtr<ID3D12Resource> m_frameBuffer[3];

        Device* m_device;
        CommandQueue* m_queue;
        Descriptor* m_rtv;

        DXGI_FORMAT m_backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

        unsigned int m_currentframeBufferIndex = 0;

        HWND m_hwnd;
      };
    }
  }
}