#pragma once

int main()
{
    auto app = Me::CreateApplication();
    if(!app->Run())
    {

    }

    delete app;

#ifdef PLATFORM_WINDOWS
	_CrtDumpMemoryLeaks();
#endif

    return 0;
}