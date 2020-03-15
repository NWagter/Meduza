#pragma once

namespace me {
	class Meduza;
}

class Sandbox
{
public:
	Sandbox();
	~Sandbox();

	void Run();


private:
	void Update(float);

	me::Meduza* m_meduza = nullptr;
	float m_colour[4];
};

