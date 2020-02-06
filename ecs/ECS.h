/* Author: GarRaptor
 * Description: Interface to the Entity Component System
 */

#pragma once

#include <cstdio>
#include "Common.h"
#include "EntityStore.h"
#include "ComponentStore.h"
#include "Systems.h"

namespace ecs {

    EntityId getNewEntityId(const std::string entityName = "") {
        static EntityId entityId = 5;
        // TODO: create new entity in EntityStore
        //  and pass entityName for lookup table in EntityStore
        return entityId;
    }

    void saveEntity(EntityId entityId)
    {
        entity::EntityStore::getInstance()->addEntity(entityId);
    }

    void rmEntity(EntityId entityID);

    template <typename T>
    void addComponent(EntityId entityId, T& component)
    {
        component.entityID = entityId;
        component::ComponentStore* componentStore = component::ComponentStore::getInstance();

        std::printf("\n\n%s: { x: %d, y: %d, id: %d }\n", T::ID().c_str(), component.x, component.y, component.entityID);

        // TODO: EntityStore needs a map<entityId, map<componentID, componentPtr>>

        // TODO: get T* from addComponent method and store that in EntityStore
//        componentStore->addComponent<T>(component);

        // TODO: pass ptr to addComponent (void*) for quick access lookup,
        //  and entityId so we know which entity
//        entity::EntityStore::getInstance()->addComponent(T::ID());
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
