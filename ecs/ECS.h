/* Author: GarRaptor
 * Description: Interface to the Entity Component System
 */

#pragma once

#include <map>
#include <vector>

#include "Entity.h"
#include "ComponentStore.h"
#include "Systems.h"


int g_EntityID = 0;


#define Component(comp, data) \
    struct comp {\
        static const std::string name;\
        int entityID;\
        data\
    };\
    const std::string comp::name = #comp


int saveEntity()
{
    Entity::getInstance()->addEntity
}

void rmEntity(int entityID);

template <typename T>
void addComponent(const T& component)
{
    Entity::getInstance()->addComponent(component.name);
}

template <typename T> void rmComponent(const std::string& name);
template <typename T> T* getComponent(int entityID, const std::string& name);
template <typename T> void activateComponent(int entityID, const std::string& name);
template <typename T> void deactivateComponent(int entityID, const std::string& name);

// void addSystem(void (funcPtr)(void));
// void rmSystem(void (funcPtr)(void));
// void enableSystem(void (funcPtr)(void));
// void disableSystem(void (funcPtr)(void));

template <typename T> T* getComponentList(const std::string& name);
int* getEntityList(const std::string* componentTuple);
// TODO: get ComponentList with list of entity IDs
