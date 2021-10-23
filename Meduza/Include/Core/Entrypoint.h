#pragma once

int main()
{
    auto app = Me::CreateApplication();
    if(!app->Run())
    {

    }

    delete app;

	_CrtDumpMemoryLeaks();
    return 0;
}