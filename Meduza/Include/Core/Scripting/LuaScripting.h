#pragma once

namespace Me
{
    namespace Scripting
    {
        class LuaScripting
        {
            public:
                LuaScripting();
                ~LuaScripting();

                void ExecuteScript(std::string a_script, float a_dt);

                static LuaScripting* GetInstance() {return ms_instance;}
            private:
                static LuaScripting* ms_instance;
        };
    }
}