#include "PCH.h"

#include "MeduzaIncluder.h"

#include "Games/Chess.h"

#include "Systems/ChessSystem.h"
#include "Systems/PawnSystem.h"
#include "Systems/ChessboardSystem.h"

Chess::Chess()
{   
}

Chess::~Chess()
{

}

void Chess::InitGame()
{    
    new ChessSystem();
    new PawnSystem();
    new ChessboardSystem();
}