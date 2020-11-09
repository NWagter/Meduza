#pragma once

#include "EntityTypes.h"

namespace Me
{
    class Entity;
    class BaseSystem;
    struct BaseComponent;

    class EntityManager
    {
        public:

        static EntityManager* CreateEntityManager();
        static void DestroyEntityManager();
        inline static EntityManager* GetEntityManager() {return ms_entityManager;}

        static void AddSystem(BaseSystem*);

        static Entity* CreateEntity();
        static bool AddComponent(Entity*, BaseComponent*);

        void Update(float);
        
        std::vector<Entity*> GetEntities(EntityFilter);

        private:
        EntityManager();
        ~EntityManager();
        static EntityManager* ms_entityManager;

        std::vector<Entity*> m_entities;
        std::vector<BaseSystem*> m_systems;

        friend BaseSystem;
    };
}