#include "PosComponent.h"
#include "ComponentKeys.h"


PosComponent::PosComponent(): _x(0), _y(0), Component(POSITION)
{}

void PosComponent::getPos(int &x, int &y) const
{
    x = _x;
    y = _y;
}

void PosComponent::setPos(int x, int y)
{
    _x = x;
    _y = y;
}
