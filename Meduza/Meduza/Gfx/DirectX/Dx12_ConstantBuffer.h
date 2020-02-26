#pragma once

class Dx12_Device;
class Dx12_Descriptor;

class Dx12_ConstantBuffer {
public:
	Dx12_ConstantBuffer(const Dx12_Device&, Dx12_Descriptor&);


	ConstantBuffer m_constBufferData; //const buffer data
	void CopyData(int);

	inline UINT8* GetBufferGPUAdress() { return m_bufferDataGPUAdress; }
	inline ID3D12Resource* GetResource() { return m_cBufferResource; }
	inline int GetBufferAlignment() { return m_constBufferAlignment; }

private:
	ID3D12Resource* m_cBufferResource;

	UINT8* m_bufferDataGPUAdress; // this is a pointer to the memory location we get when we map our constant buffer
	int m_constBufferAlignment = (sizeof(ConstantBuffer) + 255) & ~255;
};
