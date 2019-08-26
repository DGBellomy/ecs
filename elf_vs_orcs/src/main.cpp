#include "entity.h"
#include "component.h"

// Find the ring

int main()
{
    // generic board game (pieces placed on a board, each with specific rules associated with them)
    // create pieces: placement, actions
    // create a board (contains pieces): size, pieces, placement
    // create a game (contains a board): rules, logic

    return 0;
}

Entity* createPiece(Component** componentList)
{
    Entity* piece = new Entity();
    return piece;
}

Entity* createBoard(Component** componentList)
{
    return nullptr;
}

Entity* createGame(Component** componentList)
{
    return nullptr;
}
