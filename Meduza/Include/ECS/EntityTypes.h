#pragma once

using EntityID = uint64_t;
using ComponentID = uint64_t;
using SystemID = uint64_t;

using EntityFilter = std::set<ComponentID>;

enum class Components : uint16_t
{
    Tag = 1,
    Transform = 2,
    Editor = 3,

    Render = 4,
    DebugRender = 5,

    Camera = 6,

    Scripting = 7,

    Physics = 8,
    Collider = 9,
    ColliderTag = 10,
    BoxCollider2D = 11,
    BoxCollider3D = 12,
    CircleCollider = 13,
    SphereCollider = 14,

    AgentComponent = 15,
    NavSurfaceComponent = 16,

    ParticleComponent = 17,
    ParticleSystemComponent = 18,
    
    Game
};