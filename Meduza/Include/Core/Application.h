#pragma once
namespace Me
{
    class Meduza;
	struct Renderable;

    namespace Math
    {
        class Vec2;
    }

    class Application
    {
    public:
        Application();
        virtual ~Application();

        virtual void OnUpdate(float);
        virtual void OnInitilized() = 0;
        virtual void OnClose() = 0;
        
        bool Run();
    protected:
        virtual void SetName(std::string) final;
        Math::Vec2 GetScreenSize();

    private:
        Meduza* m_meduza;
    };

	Application* CreateApplication();
}