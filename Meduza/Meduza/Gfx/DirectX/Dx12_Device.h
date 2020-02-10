#pragma once
#include "../Common/Device.h"

class Dx12_Device : public Device {

public :
	~Dx12_Device();

	virtual void InitDevice() override;
	virtual void DestroyDevice() override;

	Microsoft::WRL::ComPtr<ID3D12Device2> m_device;
	Microsoft::WRL::ComPtr<IDXGIFactory4> m_factory;
};