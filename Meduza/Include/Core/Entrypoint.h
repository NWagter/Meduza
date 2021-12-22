#pragma once

int main()
{
#ifdef PLATFORM_WINDOWS
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    auto app = Me::CreateApplication();
    if(!app->Run())
    {

    }

    delete app;

#ifdef PLATFORM_WINDOWS
	//_CrtDumpMemoryLeaks();
#endif

    return 0;
}