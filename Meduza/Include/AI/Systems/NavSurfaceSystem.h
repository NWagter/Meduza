#pragma once

#include "ECS/BaseSystem.h"

namespace Me
{    
    struct TagComponent;

    namespace AI
    {
        struct NavSurfaceComponent;
        struct NavField;

        class NavSurfaceSystem : public BaseSystem<NavSurfaceComponent, TagComponent>
        {
        public:
            NavSurfaceSystem();
            ~NavSurfaceSystem();

            void OnUpdate(float a_dt) override;

        private:
            std::map<EntityID, NavField*> m_fields;
        };
        
    }
}