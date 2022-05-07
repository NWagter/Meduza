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
    ME_PROFILE_FUNC("FluidDragSystem");
    
    for(auto& compTuple : m_components)
    {
        PhysicsComponent* pC = std::get<PhysicsComponent*>(compTuple);
        
        Math::Vector3 velocity = pC->m_velocity;
        float vel = velocity.Lenght();

        if(vel <= 0)
        {
            continue;
        }

        float drag = pC->m_drag * std::pow(vel, gs_dragExponent);
        Math::Vector3 dragForce = (velocity.Normalize() * drag).Inverse();

        if (!dragForce.IsNan())
        {
            pC->m_velocity += dragForce * a_dt;
        }
    }
}

