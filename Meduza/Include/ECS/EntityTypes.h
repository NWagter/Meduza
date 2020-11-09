#pragma once

using EntityID = uint16_t;
using ComponentID = uint16_t;
using SystemID = uint16_t;

using EntityFilter = std::vector<ComponentID>;

enum class Components
{
    Transform,
    Render,

    Game
};