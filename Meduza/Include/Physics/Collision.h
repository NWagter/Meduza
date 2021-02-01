#pragma once

#include "Math/MeduzaMath.h"

namespace Me
{
    namespace Physics
    {
        struct CollisionData;
        struct PhysicsBody;
        struct BodyBox2D;
        struct BodyCircle;

        class Collision
        {
        public:
            static bool CheckCollision(PhysicsBody*, PhysicsBody*, CollisionData& a_data);

            // ==== 2D collision Checks
            static bool Box2DToBox2D(BodyBox2D*, BodyBox2D*, CollisionData& a_data);
            static bool Box2DToCircle(BodyBox2D*, BodyCircle*, CollisionData& a_data);
            static bool CircleToBox2D(BodyCircle*, BodyBox2D*, CollisionData& a_data);
            static bool CircleToCircle(BodyCircle*, BodyCircle*, CollisionData& a_data);
        };  
    }
}