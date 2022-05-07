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
        Context(Window& a_window, Device* a_device);
        ~Context();
        
        void SwapBuffer(CommandList& a_cmd);
        void Resize(float const a_width, float const a_height) override;

        void CreateSwapchain();
        void SetQueue(CommandQueue& a_queue);
        inline Microsoft::WRL::ComPtr<IDXGISwapChain4> GetSwapChain() { return m_swapChain; }
        inline ID3D12Resource* GetCurrentBuffer() { return m_frameBuffer[m_currentframeBufferIndex].Get(); }
        inline Descriptor* GetRTV() { return m_rtv;}
        inline Microsoft::WRL::ComPtr<ID3D12Resource> GetBuffers(int const a_index) { return m_frameBuffer[a_index]; }

        inline CommandQueue* GetQueue() { return m_queue; }

        void ClearRTV();
        void CreateRTV(Descriptor& a_rtv, Descriptor& a_srv);
        void Resize(int const a_width, int const a_height);
        Math::Vector2 Resize();

        inline DXGI_FORMAT GetFormat() { return m_backBufferFormat; }
        inline HWND GetHWND() const { return m_hwnd; }
        inline unsigned int GetCurrentFrameIndex() const { return m_currentframeBufferIndex; }
        inline bool GetResize() {return m_resize;}
        float m_width, m_height;
      private:
        bool m_resize = false;
        void CreateSwapChain();
        Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapChain;
        Microsoft::WRL::ComPtr<ID3D12Resource> m_frameBuffer[3];

        Device* m_device;
        CommandQueue* m_queue;
        Descriptor* m_rtv;
        Descriptor* m_srv;

        DXGI_FORMAT m_backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

        unsigned int m_currentframeBufferIndex = 0;

        HWND m_hwnd;
      };
    }
  }
}