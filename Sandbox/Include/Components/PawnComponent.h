#pragma once

#include "Components/GameComponents.h"
#include "Math/MeduzaMath.h"

enum class PawnTypes : uint8_t
{
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

enum class PawnColour : uint8_t
{
    White,
    Black
};

struct TileComponent;

struct PawnComponent : Me::BaseComponent
{    

    Me::Math::Vec3 m_newPos;

    PawnTypes m_type;
    PawnColour m_colour;

    TileComponent* m_tile;
    bool m_moving = false;
    
    static ComponentID s_componentID;
};