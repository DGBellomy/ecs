#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include "component.h"

#define EntityPair std::pair<unsigned int, Component>
#define EntityMap std::map<unsigned int, Component>

class Entity {
    EntityMap componentDict;

public:
    bool add(Component component);
    bool remove(unsigned int componentKey);
    Component* get(unsigned int componentKey);
};

#endif //ENTITY_H
