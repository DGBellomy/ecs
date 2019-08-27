#ifndef POS_COMP_H
#define POS_COMP_H

#include "component.h"

// Lets an entity have position in a 2D world.
class PosComponent: public Component {
    int _x, _y;
public:
    PosComponent();

    void getPos(int &x, int &y) const;
    void setPos(int x, int y);
};

#endif //POS_COMP_H
