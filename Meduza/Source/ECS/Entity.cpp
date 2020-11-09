#include "MePCH.h"
#include "ECS/Entity.h"

#include "ECS/BaseComponent.h"

Me::Entity::Entity()
{

}

Me::Entity::~Entity()
{
    for(auto c : m_components)
    {
        delete c.second;
    }

    m_components.clear();
}

Me::BaseComponent* Me::Entity::GetComponent(ComponentID a_id)
{
    auto comp = m_components[a_id];
    if(comp == nullptr)
    {
        ME_CORE_LOG("Component is not added to this Entity");
    }

    return comp;
}

bool Me::Entity::HasComponent(ComponentID a_id)
{
    auto comp = m_components[a_id];
    if(comp == nullptr)
    {
        return false;
    }

    return true;
}

bool Me::Entity::AddComponent(BaseComponent* a_comp)
{
    if(HasComponent(a_comp->GetComponentID()))
    {
        return false;
    }

    m_components[a_comp->GetComponentID()] = a_comp;
    return true;
}