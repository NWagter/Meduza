#pragma once

#define NAVFIELD_VOID -1
#define NAVFIELD_EMPTY 0
#define NAVFIELD_OCCUPIED 1

namespace Me
{
    namespace AI
    {
        struct NavField
        {
            Me::Math::Vec2 m_gridSize;
            Me::Math::Vec2 m_cellSize;

            int m_xCells;
            int m_yCells;

            char* m_grid;

            NavField(Me::Math::Vec2 a_gridSize, Me::Math::Vec2 a_cellSize)
            {
                m_gridSize = a_gridSize;
                m_cellSize = a_cellSize;

                m_xCells = (int)(m_gridSize.m_x / m_cellSize.m_x);
                m_yCells = (int)(m_gridSize.m_y / m_cellSize.m_y);
                

                m_grid = new char[m_xCells * m_yCells];

                for(int i = 0; i < m_xCells * m_yCells;i++)
                {
                    m_grid[i] = NAVFIELD_VOID;
                }
            }
        };
    }
}