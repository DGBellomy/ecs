#ifndef MOVE_COMP_H
#define MOVE_COMP_H

#include "component.h"

#define MOVE "move"

// Lets an entity move in a 2D world.
// depends on the entity to have a PosComponent
class MoveComponent: public Component {
    // TODO: Requires either a PosComponent or an Entity with a PosComponent ???
public:
    MoveComponent();

    void move(int x, int y);
};

#endif //MOVE_COMP_H
