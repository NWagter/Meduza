#include "PCH.h"
#include "MeduzaIncluder.h"

#include "Games/Chess/ChessHelper.h"

#include "Components/Chess/ChessPawnComponent.h"
#include "Components/Chess/ChessBoardComponent.h"

void Chess::ChessHelper::LogType(ChessPawnComponent& a_pawn)
{
    switch (a_pawn.m_pawnType)
    {
        case Pawns::Pawn :
            ME_GAME_LOG("Pawn \n");
            break;
        case Pawns::Knight :
            ME_GAME_LOG("Knight \n");
        break;
        case Pawns::Rook :
            ME_GAME_LOG("Rook \n");
        break;
        case Pawns::Bishop :
            ME_GAME_LOG("Bishop \n");
        break;
        case Pawns::Queen :
            ME_GAME_LOG("Queen \n");
        break;
        case Pawns::King :
            ME_GAME_LOG("King \n");
        break;
    }
}

std::vector<std::pair<int,int>> Chess::ChessHelper::GetPossibleMoves(ChessPawnComponent& a_pawn, ChessBoardComponent* a_board)
{
    std::vector<std::pair<int,int>> moves;

    int x = static_cast<int>(a_pawn.m_boardPos.m_x);
    int y = static_cast<int>(a_pawn.m_boardPos.m_y);

//Pawn
    if(a_pawn.m_pawnType == Pawns::Pawn)
    {
        if(a_pawn.m_pawnColour == Colour::White)
        {
            if(a_board->m_board[x][y + 1] == nullptr)
            {
                moves.push_back(std::pair<int,int>(x, y + 1));
                if(a_pawn.m_firstMove && a_board->m_board[x][y + 2] == nullptr)
                {
                    moves.push_back(std::pair<int,int>(x, y + 2));
                }
            }
            if(a_board->m_board[x + 1][y +1] != nullptr)
            {
                moves.push_back(std::pair<int,int>(x + 1, y + 1));
            }
            if(a_board->m_board[x - 1][y + 1] != nullptr)
            {
                moves.push_back(std::pair<int,int>(x - 1, y + 1));
            }
        }
        else
        {
            if(a_board->m_board[x][y - 1] == nullptr)
            {
                moves.push_back(std::pair<int,int>(x, y - 1));
                if(a_pawn.m_firstMove && a_board->m_board[x][y - 2] == nullptr)
                {
                    moves.push_back(std::pair<int,int>(x, y - 2));
                }
            }
            if(a_board->m_board[x + 1][y - 1] != nullptr)
            {
                moves.push_back(std::pair<int,int>(x + 1, y - 1));
            }
            if(a_board->m_board[x - 1][y - 1] != nullptr)
            {
                moves.push_back(std::pair<int,int>(x - 1, y - 1));
            }
        }
        
    }
//Rook
    if(a_pawn.m_pawnType == Pawns::Rook || a_pawn.m_pawnType == Pawns::Queen)
    {
        for(int rX = x; rX < gs_boardWidth; ++rX)
        {
            auto p = a_board->m_board[rX][y];
            if(p == &a_pawn)
            {
                continue;
            }

            if(p == nullptr)
            {
                moves.push_back(std::pair<int,int>(rX, y));
            }
            else if(p->m_pawnColour != a_pawn.m_pawnColour)
            {
                moves.push_back(std::pair<int,int>(rX, y));
                break;
            }
            else if(p->m_pawnColour == a_pawn.m_pawnColour)
            {
                break;
            }
        }  
        for(int rX = x; rX >= 0; --rX)
        {
            auto p = a_board->m_board[rX][y];
            if(p == &a_pawn)
            {
                continue;
            }

            if(p == nullptr)
            {
                moves.push_back(std::pair<int,int>(rX, y));
            }
            else if(p->m_pawnColour != a_pawn.m_pawnColour)
            {
                moves.push_back(std::pair<int,int>(rX, y));
                break;
            }
            else if(p->m_pawnColour == a_pawn.m_pawnColour)
            {
                break;
            }
        }
    
        for(int rY = y; rY < gs_boardHeight; ++rY)
        {
            auto p = a_board->m_board[x][rY];            
            if(p == &a_pawn)
            {
                continue;
            }

            if(p == nullptr)
            {
                moves.push_back(std::pair<int,int>(x, rY));
            }
            else if(p->m_pawnColour != a_pawn.m_pawnColour)
            {
                moves.push_back(std::pair<int,int>(x, rY));
                break;
            }
            else if(p->m_pawnColour == a_pawn.m_pawnColour)
            {
                break;
            }
        }  
        for(int rY = y; rY >= 0; --rY)
        {
            auto p = a_board->m_board[x][rY];
            if(p == &a_pawn)
            {
                continue;
            }

            if(p == nullptr)
            {
                moves.push_back(std::pair<int,int>(x, rY));
            }
            else if(p->m_pawnColour != a_pawn.m_pawnColour)
            {
                moves.push_back(std::pair<int,int>(x, rY));
                break;
            }
            else if(p->m_pawnColour == a_pawn.m_pawnColour)
            {
                break;
            }
        }  
    
    }
//Bishop
    if(a_pawn.m_pawnType == Pawns::Bishop || a_pawn.m_pawnType == Pawns::Queen)
    {
        int rX = x;
        for(int rY = y; rY < gs_boardHeight; ++rY, ++rX)
        {       
            if(rX > gs_boardWidth - 1)
            {
                break;
            }
            auto p = a_board->m_board[rX][rY]; 

            if(p == &a_pawn)
            {
                continue;
            }

            if(p == nullptr)
            {
                moves.push_back(std::pair<int,int>(rX, rY));
            }
            else if(p->m_pawnColour != a_pawn.m_pawnColour)
            {
                moves.push_back(std::pair<int,int>(rX, rY));
                break;
            }
            else if(p->m_pawnColour == a_pawn.m_pawnColour)
            {
                break;
            }
        } 
        rX = x;
        for(int rY = y; rY < gs_boardHeight; ++rY, --rX)
        {
            if(rX < 0)
            {
                break;
            }

            auto p = a_board->m_board[rX][rY];       

            if(p == &a_pawn)
            {
                continue;
            }

            if(p == nullptr)
            {
                moves.push_back(std::pair<int,int>(rX, rY));
            }
            else if(p->m_pawnColour != a_pawn.m_pawnColour)
            {
                moves.push_back(std::pair<int,int>(rX, rY));
                break;
            }
            else if(p->m_pawnColour == a_pawn.m_pawnColour)
            {
                break;
            }
        }   
        rX = x;
        for(int rY = y; rY >= 0; --rY, ++rX)
        {            
            if(rX > gs_boardWidth - 1)
            {
                break;
            }

            auto p = a_board->m_board[rX][rY];     

            if(p == &a_pawn)
            {
                continue;
            }

            if(p == nullptr)
            {
                moves.push_back(std::pair<int,int>(rX, rY));
            }
            else if(p->m_pawnColour != a_pawn.m_pawnColour)
            {
                moves.push_back(std::pair<int,int>(rX, rY));
                break;
            }
            else if(p->m_pawnColour == a_pawn.m_pawnColour)
            {
                break;
            }
        }
        rX = x;
        for(int rY = y; rY >= 0; --rY, --rX)
        {
            if(rX < 0)
            {
                break;
            }

            auto p = a_board->m_board[rX][rY]; 

            if(p == &a_pawn)
            {
                continue;
            }

            if(p == nullptr)
            {
                moves.push_back(std::pair<int,int>(rX, rY));
            }
            else if(p->m_pawnColour != a_pawn.m_pawnColour)
            {
                moves.push_back(std::pair<int,int>(rX, rY));
                break;
            }
            else if(p->m_pawnColour == a_pawn.m_pawnColour)
            {
                break;
            }
        }
    }
//Knight
    if(a_pawn.m_pawnType == Pawns::Knight)
    {
        std::vector<std::pair<int,int>> kMoves;
        kMoves.push_back(std::pair<int,int>(x + 2, y + 1));
        kMoves.push_back(std::pair<int,int>(x - 2, y + 1));
        kMoves.push_back(std::pair<int,int>(x + 2, y - 1));
        kMoves.push_back(std::pair<int,int>(x - 2, y - 1));

        kMoves.push_back(std::pair<int,int>(x + 1, y + 2));
        kMoves.push_back(std::pair<int,int>(x - 1, y + 2));
        kMoves.push_back(std::pair<int,int>(x + 1, y - 2));
        kMoves.push_back(std::pair<int,int>(x - 1, y - 2));

        for(auto kM : kMoves)
        {
            if(kM.first < 0 || kM.first >= 8 || kM.second < 0 || kM.second >= 8)
            {
                continue;
            }

            auto p = a_board->m_board[kM.first][kM.second];
            if(p == nullptr)
            {
                moves.push_back(kM);
            }
            else if(p->m_pawnColour != a_pawn.m_pawnColour)
            {
                moves.push_back(kM);
            }
        }
    }

    if(a_pawn.m_pawnType == Pawns::King)
    {
        moves.push_back(std::pair<int,int>(x + 1, y));
        moves.push_back(std::pair<int,int>(x + 1, y - 1));
        moves.push_back(std::pair<int,int>(x + 1, y + 1));

        moves.push_back(std::pair<int,int>(x - 1, y));
        moves.push_back(std::pair<int,int>(x - 1, y - 1));
        moves.push_back(std::pair<int,int>(x - 1, y + 1));

        moves.push_back(std::pair<int,int>(x, y - 1));
        moves.push_back(std::pair<int,int>(x, y + 1));
    }

    
    return moves;
}

bool Chess::ChessHelper::CanMove(std::pair<int,int> a_pos, std::vector<std::pair<int,int>> a_moves)
{
    for(auto move : a_moves)
    {
        if(move == a_pos)
        {
            return true;
        }
    }

    return false;
}

std::pair<int,int> Chess::ChessHelper::GetBestMove(std::vector<std::pair<int,int>> a_moves, ChessBoardComponent* a_board)
{
    int value = 0;
    int moveIndex = 0;

    int cIndex = 0;

    for(auto m : a_moves)
    {
        if(m.first < 0 || m.first >= gs_boardWidth || m.second < 0 || m.second >= gs_boardHeight)
        {        
            cIndex++;
            continue;
        }

        auto p = a_board->m_board[m.first][m.second];
        float v = 0;
        if(p != nullptr)
        {
            v = GetValue(*p);            
        }else
        {
            v = -(rand() % 5);
        }        

        if(v < value)
        {
            value = v;
            moveIndex = cIndex;
        }
        
        cIndex++;
    }


    return std::pair<int,int>(moveIndex, value);
}

int Chess::ChessHelper::GetValue(ChessPawnComponent& a_pawn)
{
    int v;
    switch (a_pawn.m_pawnType)
    {
        case Pawns::Pawn :
            v = gs_pawnValue;
            break;
        case Pawns::Knight :
            v = gs_knighValue;
        break;
        case Pawns::Rook :
            v = gs_rookValue;
        break;
        case Pawns::Bishop :
            v = gs_bishnopValue;
        break;
        case Pawns::Queen :
            v = gs_queenValue;
        break;
        case Pawns::King :
            v = gs_kingValue;
        break;
    }

    if(a_pawn.m_pawnColour == Colour::White && v != 0)
    {
        v = v * -1;
    }

    return v;
}