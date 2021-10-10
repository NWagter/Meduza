#pragma once

using EntityID = uint64_t;
using ComponentID = uint64_t;
using SystemID = uint64_t;

using EntityFilter = std::set<ComponentID>;

enum class Components : uint16_t
{
    Tag,
    Transform,
    Editor,

    Render,
    DebugRender,

    Camera,

    Scripting,

    Physics,
    Collider,
    ColliderTag,
    BoxCollider2D,
    BoxCollider3D,
    CircleCollider,
    SphereCollider,

    AgentComponent,
    NavSurfaceComponent,
    
    Game
};