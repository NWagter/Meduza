#include "MePCH.h"
#include "Core/Scripting/API/Lua_Events.h"

#include "MeduzaIncluder.h"

void Me::Scripting::Lua_API::Lua_Events::RegisterEventFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_OnKeyUp", lua_OnKeyUp);
    lua_register(a_luaState, "_OnKeyDown", lua_OnKeyDown);    
}

int Me::Scripting::Lua_API::Lua_Events::lua_OnKeyUp(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    Me::Event::KeyCode key = (Me::Event::KeyCode)lua_tonumber(a_luaState, -1);

    if(Event::EventSystem::GetEventSystem()->KeyUp(key))
    {
        lua_pushnumber(a_luaState, 1);        
    }
    else
    {
        lua_pushnumber(a_luaState, 0); 
    }

    return 1;
}

int Me::Scripting::Lua_API::Lua_Events::lua_OnKeyDown(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    Me::Event::KeyCode key = (Me::Event::KeyCode)lua_tonumber(a_luaState, -1);

    if(Event::EventSystem::GetEventSystem()->KeyDown(key))
    {
        lua_pushnumber(a_luaState, 1);        
    }
    else
    {
        lua_pushnumber(a_luaState, 0); 
    }

    return 1;
}