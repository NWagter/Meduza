#include "MePCH.h"
#include "AI/Systems/NavSurfaceSystem.h"

#include "AI/NavField.h"
#include "AI/Components/NavSurfaceComponent.h"

        
Me::AI::NavSurfaceSystem::NavSurfaceSystem()
{
    m_executeMask = EXECUTE_ALL;
}

Me::AI::NavSurfaceSystem::~NavSurfaceSystem()
{
    for(auto field : m_fields)
    {
        if(field.second != nullptr)
        {
            delete field.second;
        }
    }
}

void Me::AI::NavSurfaceSystem::OnUpdate(float a_dt)
{
    for(int i = 0; i < m_entities.size(); i++)
    {
        auto navC = std::get<NavSurfaceComponent*>(m_components[i]);

        if(!navC->m_generated &&
         navC->m_gridSize.m_x > 0 && navC->m_gridSize.m_y > 0 &&
         navC->m_cellSize.m_x > 0 && navC->m_cellSize.m_y > 0)
        {
            NavField* field = navC->Generate();

            m_fields[m_entities[i]] = field;
        }

        if(navC->m_printGrid)
        {
            NavField* field = m_fields[m_entities[i]];

            if(field == nullptr)
            {
                continue;
            }

            printf("--------------------------------");
            printf("\n");
            printf("%s", std::get<TagComponent*>(m_components[i])->m_tag.c_str());
            printf("\n");
            printf("--------------------------------");
            printf("\n");

            for(int y =0;y < field->m_yCells; y++)
            {
                for(int x = 0; x < field->m_xCells;x++)
                {
                    char cell = field->m_grid[y + ( x * y)];
                    if(cell == NAVFIELD_VOID)
                    {
                        printf(" -1 ");
                    }
                    if(cell == NAVFIELD_EMPTY)
                    {
                        printf(" 0 ");
                    }                   
                    if(cell == NAVFIELD_OCCUPIED)
                    {
                        printf(" 1 ");
                    }
                }
                printf("\n");
            }
            printf("--------------------------------");
            printf("\n");

            navC->m_printGrid = false;
        }

    }
}