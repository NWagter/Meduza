#pragma once

#include "Meduza.h"

int main()
{
    auto app = Me::CreateApplication();
    if(!app->Run())
    {

    }

    delete app;

    return 0;
}