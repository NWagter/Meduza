#pragma once
class Camera
{
public:

	DirectX::XMFLOAT3 m_EyePos = { 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT4X4 m_View = Dx12Helper::Identity4x4();
	DirectX::XMFLOAT4X4 m_Proj = Dx12Helper::Identity4x4();
private:

};

