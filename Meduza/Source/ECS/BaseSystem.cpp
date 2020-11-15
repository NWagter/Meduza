#include "MePCH.h"
#include "ECS/BaseSystem.h"

#include "ECS/EntityManager.h"

Me::ECSSystem::ECSSystem()
{
    EntityManager::AddSystem(this);
}