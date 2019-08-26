#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include "component.h"

class Entity {
    std::map<const char*, Component> componentDict;

public:
    bool add(Component component);
    bool remove(const char* componentName);
    Component* get(const char* componentName);
};

#endif //ENTITY_H
