#pragma once

using EntityID = uint64_t;
using ComponentID = uint64_t;
using SystemID = uint64_t;

using EntityFilter = std::set<ComponentID>;

enum class Components
{
    Transform,
    Render,
    Camera,

    Game
};