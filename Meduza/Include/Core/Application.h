#pragma once
namespace Me
{
    class Meduza;
	struct Renderable;

    class Application
    {
        public:
        Application();
        virtual ~Application();

        virtual void OnUpdate(float);
        virtual void OnInitilized() = 0;
        virtual void OnClose() = 0;
        
        bool Run();

        private:
        Meduza* m_meduza;
		Renderable* m_renderable;
    };

	Application* CreateApplication();
}