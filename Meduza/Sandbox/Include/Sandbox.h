#pragma once

namespace meduza
{
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

	meduza::Meduza* m_meduza = nullptr;
	float m_colour[4];
};

