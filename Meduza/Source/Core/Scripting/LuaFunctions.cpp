#include "MePCH.h"
#include "Core/Scripting/LuaFunctions.h"

#include "MeduzaIncluder.h"

#include "Core/Scripting/API/Lua_Entities.h"
#include "Core/Scripting/API/Lua_Prefabs.h"

#include "Core/Scripting/API/Lua_Events.h"

#include "Core/Scripting/API/Lua_Math.h"
#include "Core/Scripting/API/Lua_Transform.h"
#include "Core/Scripting/API/Lua_Physics.h"

#include "Core/Scripting/API/Lua_Graphics.h"

#include "Core/Scripting/API/Lua_SceneManager.h"

#include "Core/Scripting/ScriptComponent.h"
#include "Platform/General/FileSystem/FileSystem.h"



void Me::Scripting::LuaFunctions::RegisterFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_CallFunction", lua_CallFunction);

    Lua_API::Lua_Entities::RegisterEntityFunctions(a_luaState);
    Lua_API::Lua_Prefabs::RegisterPrefabsFunctions(a_luaState);

    Lua_API::Lua_Events::RegisterEventFunctions(a_luaState);

    Lua_API::Lua_Math::RegisterMathFunctions(a_luaState);
    Lua_API::Lua_Transform::RegisterTransformFunctions(a_luaState);
    Lua_API::Lua_Physics::RegisterPhysicsFunctions(a_luaState);

    Lua_API::Lua_Graphics::RegisterGraphicsFunctions(a_luaState);
    Lua_API::Lua_SceneManager::RegisterSceneManagerFunctions(a_luaState);
}

int Me::Scripting::LuaFunctions::lua_CallFunction(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    std::string script = lua_tostring(a_luaState, 2);
    std::string function = lua_tostring(a_luaState, 3);
    EntityID entFrom = (EntityID)lua_tonumber(a_luaState, 4);

    auto sC =  EntityManager::GetEntityManager()->GetComponent<ScriptComponent>(ent);
    
    if(sC == nullptr || sC->m_luastates.empty())
    {
        return -1;
    }

    lua_State* lScript = nullptr;

    for(size_t i = 0; i < sC->m_scripts.size(); i++)
    {
        if(Files::FileSystem::GetFileName(sC->m_scripts[i]) == script)
        {
            lScript = sC->m_luastates.at(i);
            break;
        }
    }
    if(lScript == nullptr)
    {
        return -1;
    }

    lua_getglobal(lScript, function.c_str());

    if(lua_isfunction(lScript, -1) )
    {
        lua_pushnumber(lScript, (uint32_t)entFrom);
        lua_pcall(lScript,1,0,0);
    }

    return 1;
}