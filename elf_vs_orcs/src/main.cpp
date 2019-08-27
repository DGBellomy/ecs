#include "entity.h"
#include "PosComponent.h"

// Find the ring

int main()
{
    // generic board game (pieces placed on a board, each with specific rules associated with them)
    // create pieces: placement, actions
    // create a board (contains pieces): size, pieces, placement
    // create a game (contains a board): rules, logic

    return 0;
}

Entity* createElf()
{
    Entity* elf = new Entity();
    elf->add(PosComponent());
    return elf;
}

Entity* createOrc()
{
    Entity* orc = new Entity();
    orc->add(PosComponent());
    return orc;
}

Entity* createWall()
{
    Entity* wall = new Entity();
    wall->add(PosComponent());
    return wall;
}

Entity* createBoard()
{
    Entity* board = new Entity();
    return board;
}

Entity* createGame()
{
    Entity* game = new Entity();
    return game;
}
