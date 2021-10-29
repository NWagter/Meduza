#include "MePCH.h"
#include "Physics/Systems/FluidDragSystem.h"

#include "Physics/Components/PhysicsComponent.h"
#include "Core/Components/TransformComponent.h"

#include "Physics/Physics.h"

Me::Physics::FluidDragSystem::FluidDragSystem()
{

}

void Me::Physics::FluidDragSystem::OnUpdate(float a_dt)
{
    for(auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);
        
        Math::Vec3 velocity = pC->m_velocity;
        float vel = velocity.Lenght();
        float drag = pC->m_drag * std::pow(vel, 1.2f);

        if(vel == 0)
        {
            continue;
        }

        Math::Vec3 dragForce = (velocity.Normalize() * drag).Inverse();
        pC->m_velocity += dragForce * a_dt;
    }
}

