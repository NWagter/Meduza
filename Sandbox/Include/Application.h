#pragma once

namespace Me
{
    class Meduza;
}

class Application
{
    public:
    Application();
    ~Application();

    void Run();
    void Destroy();

    private:
    Me::Meduza* m_meduza;
};