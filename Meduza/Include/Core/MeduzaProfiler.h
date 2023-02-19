#pragma once

#ifdef PLATFORM_WINDOWS
    #include <optick.h>
    #define ME_ENABLE_PROFILING 1
#else
    #define ME_ENABLE_PROFILING 0
#endif

#if ME_ENABLE_PROFILING

    #define ME_PROFILE_APP(...) OPTICK_APP(__VA_ARGS__)
    #define ME_PROFILE_FRAME(...)           OPTICK_FRAME(__VA_ARGS__)
    #define ME_PROFILE_FUNC(...)            OPTICK_EVENT(__VA_ARGS__)
    #define ME_PROFILE_TAG(NAME, ...)       OPTICK_TAG(NAME, __VA_ARGS__)
    #define ME_PROFILE_SCOPE_DYNAMIC(NAME)  OPTICK_EVENT_DYNAMIC(NAME)
    #define ME_PROFILE_THREAD(...)          OPTICK_THREAD(__VA_ARGS__)
    #define ME_PROFILE_STOP(...)            OPTICK_SHUTDOWN()
    
#else
    #define ME_PROFILE_APP(...)
    #define ME_PROFILE_FRAME(...)
    #define ME_PROFILE_FUNC(...)
    #define ME_PROFILE_TAG(NAME, ...)
    #define ME_PROFILE_SCOPE_DYNAMIC(NAME)
    #define ME_PROFILE_THREAD(...) 
    #define ME_PROFILE_STOP(...)
#endif