#ifndef ENTITY_H
#define ENTITY_H

#include "component.h"

class Entity {
public:
    bool add(Component* component);
    bool remove(const char* componentName);
    Component* get(const char* componentName);
};

#endif //ENTITY_H
