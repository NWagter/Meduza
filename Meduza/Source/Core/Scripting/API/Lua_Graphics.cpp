#include "MePCH.h"
#include "Core/Scripting/API/Lua_Graphics.h"

#include "MeduzaIncluder.h"

#include "Platform/General/ResourceLibrary.h"
#include "Platform/General/Resources/TextureBase.h"

void Me::Scripting::Lua_API::Lua_Graphics::RegisterGraphicsFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_SetUV", lua_SetUV);
    lua_register(a_luaState, "_SetUV", lua_SetColour);
    lua_register(a_luaState, "_SetUV", lua_GetColour);
}

int Me::Scripting::Lua_API::Lua_Graphics::lua_SetUV(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 5) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);
    float w = lua_tonumber(a_luaState, 5);

    auto rC =  EntityManager::GetEntityManager()->GetComponent<RenderComponent>(ent);
    
    if(rC != nullptr && rC->m_texture > 0)
    {
        Math::Vec2 size = Resources::ResourceLibrary::GetInstance()->GetResource<Resources::TextureBase>(rC->m_texture)->GetSize();
        rC->m_textureCoords = Animation::GetUV(Math::Vec4(x,y,z,w), size);
    }

    return 1;
}

int Me::Scripting::Lua_API::Lua_Graphics::lua_SetColour(lua_State* a_luaState)
{
    if (lua_gettop(a_luaState) != 5) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float r = lua_tonumber(a_luaState, 2);
    float g = lua_tonumber(a_luaState, 3);
    float b = lua_tonumber(a_luaState, 4);
    float a = lua_tonumber(a_luaState, 5);

    auto rC = EntityManager::GetEntityManager()->GetComponent<RenderComponent>(ent);

    if (rC != nullptr)
    {
        rC->m_colour = Colour(r, g, b, a);
    }

    return 1;
}

int Me::Scripting::Lua_API::Lua_Graphics::lua_GetColour(lua_State* a_luaState)
{
    if (lua_gettop(a_luaState) != 5) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float r = lua_tonumber(a_luaState, 2);
    float g = lua_tonumber(a_luaState, 3);
    float b = lua_tonumber(a_luaState, 4);
    float a = lua_tonumber(a_luaState, 5);

    auto rC = EntityManager::GetEntityManager()->GetComponent<RenderComponent>(ent);

    if (rC != nullptr)
    {
        rC->m_colour = Colour(r, g, b, a);
    }

    return 1;
}