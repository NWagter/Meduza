#include "MePCH.h"
#include "Core/Scripting/LuaFunctions.h"

#include "MeduzaIncluder.h"

#include "Physics/Components/ColliderComponent.h"

void Me::Scripting::LuaFunctions::RegisterFunctions(lua_State* a_luaState)
{
    lua_register(a_luaState, "_DestroyEnt", lua_DestroyEnt);
    lua_register(a_luaState, "_Translate", lua_Translate);
    lua_register(a_luaState, "_SetLocation", lua_SetLocation);
    lua_register(a_luaState, "_Move", lua_Move);
    lua_register(a_luaState, "_Rotate", lua_Rotate);
    lua_register(a_luaState, "_SetRotation", lua_SetRotation);
    lua_register(a_luaState, "_SetScale", lua_SetScale);

    
    lua_register(a_luaState, "_OnKeyUp", lua_OnKeyUp);
    lua_register(a_luaState, "_OnKeyDown", lua_OnKeyDown);

    lua_register(a_luaState, "_OnTriggerEntityName", lua_OnTriggerEntityName);
    lua_register(a_luaState, "_OnCollisionEntityName", lua_OnCollisionEntityName);

    lua_register(a_luaState, "_InstantiatePrefab", lua_InstantiatePrefab);
}

int Me::Scripting::LuaFunctions::lua_DestroyEnt(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 1) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);

    EntityManager::GetEntityManager()->DestroyEntity(ent);

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

int Me::Scripting::LuaFunctions::lua_Move(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 4) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    float x = lua_tonumber(a_luaState, 2);
    float y = lua_tonumber(a_luaState, 3);
    float z = lua_tonumber(a_luaState, 4);

    auto trans =  EntityManager::GetEntityManager()->GetComponent<TransformComponent>(ent);

    Me::Math::Mat4 transform = Me::Math::Mat4().Rotation(trans->m_rotation);
    Me::Math::Vec3 forward = transform.GetForward() * x;
    Me::Math::Vec3 right = transform.GetRight() * y;
    Me::Math::Vec3 up = transform.GetUp() * z;

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
            Physics::PhysicsComponent* c = eManager->GetComponent<Physics::PhysicsComponent>(e);

            for(auto data : c->m_triggered)
            {
                if(data.m_entity == ent)
                {
                    lua_pushnumber(a_luaState, (int)e); 
                    return 1;
                }
            }
        }
    }

    lua_pushnumber(a_luaState, 0); 

    return -1;
}

int Me::Scripting::LuaFunctions::lua_OnCollisionEntityName(lua_State* a_luaState)
{
    if(lua_gettop(a_luaState) != 2) return -1;

    EntityID ent = (EntityID)lua_tonumber(a_luaState, 1);
    const char* name = lua_tostring(a_luaState, 2);

    EntityFilter filter;
    filter.insert(TagComponent::s_componentID);
    filter.insert(Physics::ColliderTagComponent::s_componentID);
    filter.insert(Physics::PhysicsComponent::s_componentID);

    EntityManager* eManager = EntityManager::GetEntityManager();
    std::vector<EntityID> ents = eManager->GetEntities(filter);

    for(auto e : ents)
    {
        TagComponent* t = eManager->GetComponent<TagComponent>(e);

        if(t->m_tag.c_str() == name)
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

    lua_pushnumber(a_luaState, 0); 

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
    trans->m_translation = Math::Vec3(x,y,z);

    return 1;
}