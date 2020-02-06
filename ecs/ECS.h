/* Author: GarRaptor
 * Description: Interface to the Entity Component System
 */

#pragma once

#include "Common.h"
#include "EntityStore.h"
#include "ComponentStore.h"
#include "Systems.h"

namespace ecs {

    EntityId g_EntityID = 0;

    int saveEntity()
    {
        entity::EntityStore::getInstance()->addEntity();
    }

    void rmEntity(EntityId entityID);

    template <typename T>
    void addComponent(const T& component)
    {
        Entity::getInstance()->addComponent(component.name);
    }

    template <typename T> void rmComponent(ComponentId& name);
    template <typename T> T* getComponent(EntityId entityID, ComponentId& name);
    template <typename T> void activateComponent(EntityId entityID, ComponentId& name);
    template <typename T> void deactivateComponent(EntityId entityID, ComponentId& name);

// void addSystem(void (funcPtr)(void));
// void rmSystem(void (funcPtr)(void));
// void enableSystem(void (funcPtr)(void));
// void disableSystem(void (funcPtr)(void));

    template <typename T> T* getComponentList(ComponentId& name);
    int* getEntityList(ComponentId* componentTuple);
// TODO: get ComponentList with list of entity IDs

};
