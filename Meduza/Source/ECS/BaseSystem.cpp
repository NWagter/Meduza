#include "MePCH.h"
#include "ECS/BaseSystem.h"

#include "ECS/EntityManager.h"

Me::BaseSystem::BaseSystem()
{    
    EntityManager::AddSystem(this);
}