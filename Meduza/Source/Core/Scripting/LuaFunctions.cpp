#include "MePCH.h"
#include "Core/Scripting/LuaFunctions.h"

#include "MeduzaIncluder.h"

#include "Physics/Components/ColliderComponent.h"
#include "Core/Scripting/ScriptComponent.h"
#include "Platform/General/FileSystem/FileSystem.h"

#include "Platform/General/TextureLibrary.h"
#include "Platform/General/Resources/TextureBase.h"


void Me::Scripting::LuaFunctions::RegisterFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_DestroyEnt", lua_DestroyEnt);
    lua_register(a_luaState, "_GetEntityByName", lua_GetEntityByName);

    lua_register(a_luaState, "_Translate", lua_Translate);

    lua_register(a_luaState, "_SetLocation", lua_SetLocation);
    lua_register(a_luaState, "_GetLocation", lua_GetLocation);

    lua_register(a_luaState, "__GetDistance", lua_GetDistance);

    lua_register(a_luaState, "_Move", lua_Move);
    lua_register(a_luaState, "_Rotate", lua_Rotate);
    lua_register(a_luaState, "_SetRotation", lua_SetRotation);
    lua_register(a_luaState, "_SetScale", lua_SetScale);

    lua_register(a_luaState, "_FlipX", lua_FlipX);
    lua_register(a_luaState, "_FlipY", lua_FlipY);

    
    lua_register(a_luaState, "_OnKeyUp", lua_OnKeyUp);
    lua_register(a_luaState, "_OnKeyDown", lua_OnKeyDown);

    lua_register(a_luaState, "_OnTriggerEntityName", lua_OnTriggerEntityName);
    lua_register(a_luaState, "_OnCollisionEntityName", lua_OnCollisionEntityName);

    lua_register(a_luaState, "_InstantiatePrefab", lua_InstantiatePrefab);
    lua_register(a_luaState, "_CallFunction", lua_CallFunction);

    
    lua_register(a_luaState, "_SetUV", lua_SetUV);
}

int Me::Scripting::LuaFunctions::lua_DestroyEnt(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);

    EntityManager::GetEntityManager()->DestroyEntity(ent);

    lua_pushnumber(a_luaState, 1);
     
    return 1;
}

int Me::Scripting::LuaFunctions::lua_GetEntityByName(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    std::string name = lua_tostring(a_luaState, 1);

    EntityFilter filter;
    filter.insert(TagComponent::s_componentID);
    filter.insert(Physics::ColliderTagComponent::s_componentID);
    filter.insert(Physics::PhysicsComponent::s_componentID);

    EntityManager* eManager = EntityManager::GetEntityManager();
    std::vector<EntityID> ents = eManager->GetEntities(filter);

    for(auto e : ents)
    {
        TagComponent* t = eManager->GetComponent<TagComponent>(e);

        if(t->m_tag == name)
        {            
            lua_pushnumber(a_luaState, (uint64_t)e); 
            return 1;
        }
    }

    lua_pushnumber(a_luaState, 0); 

    return 0;
}

int Me::Scripting::LuaFunctions::lua_Translate(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_translation += Math::Vec3(x,y,z);

    return 0;
}

int Me::Scripting::LuaFunctions::lua_Rotate(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_rotation += Math::Vec3(x,y,z);

    return 0;
}

int Me::Scripting::LuaFunctions::lua_GetLocation(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);

    if(trans == nullptr)
        return -1;

    lua_newtable(a_luaState);

    lua_pushstring(a_luaState, "x");
    lua_pushnumber(a_luaState, trans->m_translation.m_x);
    lua_settable(a_luaState, -3);
    
    lua_pushstring(a_luaState, "y");
    lua_pushnumber(a_luaState, trans->m_translation.m_y);
    lua_settable(a_luaState, -3);
    
    lua_pushstring(a_luaState, "z");
    lua_pushnumber(a_luaState, trans->m_translation.m_z);
    lua_settable(a_luaState, -3);

    luaL_getmetatable(a_luaState, "VectorMetaTable");
    lua_setmetatable(a_luaState, -2);

    return 1;
}

int Me::Scripting::LuaFunctions::lua_GetDistance(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2) return -1;

    EntityID entA = (EntityID)lua_tonumber(a_luaState, 1);
    EntityID entB = (EntityID)lua_tonumber(a_luaState, 2);

    
    auto transA =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(entA);
    auto transB =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(entB);

    float distance = Math::Distance(transA->m_translation, transB->m_translation);

    
    lua_pushnumber(a_luaState, distance); 

    return 1;
}

int Me::Scripting::LuaFunctions::lua_Move(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);

    Me::Math::Mat4 transform = Me::Math::Mat4().Rotation(trans->m_rotation);
    
    Me::Math::Vec3 right = transform.GetRight() * x;
    Me::Math::Vec3 up = transform.GetUp() * y;
    Me::Math::Vec3 forward = transform.GetForward() * z;

    Me::Math::Vec3 movement = forward + right + up;
    trans->m_translation = trans->m_translation + (movement);

    return 0;
}

int Me::Scripting::LuaFunctions::lua_SetLocation(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_translation = Math::Vec3(x,y,z);

    return 0;
}

int Me::Scripting::LuaFunctions::lua_SetRotation(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_rotation = Math::Vec3(x,y,z);

    return 0;
}

int Me::Scripting::LuaFunctions::lua_SetScale(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    trans->m_scale = Math::Vec3(x,y,z);

    return 0;
}

int Me::Scripting::LuaFunctions::lua_FlipX(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    auto scale = trans->m_scale;
    scale.m_x = -scale.m_x;
    trans->m_scale = scale;

    return 0;
}

int Me::Scripting::LuaFunctions::lua_FlipY(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);
    auto scale = trans->m_scale;
    scale.m_y = -scale.m_y;
    trans->m_scale = scale;

    return 0;
}

int Me::Scripting::LuaFunctions::lua_OnKeyUp(lua_State* a_luaState)
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

int Me::Scripting::LuaFunctions::lua_OnKeyDown(lua_State* a_luaState)
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

int Me::Scripting::LuaFunctions::lua_OnTriggerEntityName(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    std::string name = lua_tostring(a_luaState, 2);

    EntityFilter filter;
    filter.insert(TagComponent::s_componentID);
    filter.insert(Physics::ColliderTagComponent::s_componentID);
    filter.insert(Physics::PhysicsComponent::s_componentID);

    EntityManager* eManager = EntityManager::GetEntityManager();
    std::vector<EntityID> ents = eManager->GetEntities(filter);

    for(auto e : ents)
    {
        TagComponent* t = eManager->GetComponent<TagComponent>(e);

        if(t->m_tag == name || name.empty())
        {            
            Physics::PhysicsComponent* c = eManager->GetComponent<Physics::PhysicsComponent>(ent);

            for(auto data : c->m_triggered)
            {
                if(data.m_entity == e)
                {
                    lua_pushnumber(a_luaState, (int)e); 
                    return 1;
                }
            }
        }
    }

    lua_pushnumber(a_luaState, -1); 

    return -1;
}

int Me::Scripting::LuaFunctions::lua_OnCollisionEntityName(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    std::string name = lua_tostring(a_luaState, 2);

    EntityFilter filter;
    filter.insert(TagComponent::s_componentID);
    filter.insert(Physics::ColliderTagComponent::s_componentID);
    filter.insert(Physics::PhysicsComponent::s_componentID);

    EntityManager* eManager = EntityManager::GetEntityManager();
    std::vector<EntityID> ents = eManager->GetEntities(filter);

    for(auto e : ents)
    {
        TagComponent* t = eManager->GetComponent<TagComponent>(e);

        if(t->m_tag == name)
        {            
            Physics::PhysicsComponent* c = eManager->GetComponent<Physics::PhysicsComponent>(e);

            for(auto data : c->m_collided)
            {
                if(data.m_entity == ent)
                {
                    lua_pushnumber(a_luaState, (int)e); 
                    return 1;
                }
            }
        }
    }

    lua_pushnumber(a_luaState, -1); 

    return -1;
}

int Me::Scripting::LuaFunctions::lua_InstantiatePrefab(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    
    std::string path = lua_tostring(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    size_t pos = path.find("Assets"); //find location of word
    path.erase(0,pos); //delete everything prior to location found
    std::replace(path.begin(), path.end(), '\\', '/');

    EntityID newEntity = Serialization::Serializer::GetInstance()->DeserializeEntity(path);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(newEntity);
    
    if(trans == nullptr)
    {
        return -1;
    }

    trans->m_translation = Math::Vec3(x,y,z);

    lua_pushnumber(a_luaState, (uint64_t)newEntity); 
    return 1;
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
        lua_pushnumber(lScript, (uint64_t)entFrom);
        lua_pcall(lScript,1,0,0);
    }

    return 1;
}

int Me::Scripting::LuaFunctions::lua_SetUV(lua_State* a_luaState)
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
        Math::Vec2 size = Resources::TextureLibrary::GetTexture(rC->m_texture)->GetSize();
        rC->m_textureCoords = Animation::GetUV(Math::Vec4(x,y,z,w), size);
    }

    return 1;
}