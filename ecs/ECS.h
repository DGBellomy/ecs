/* Author: GarRaptor
 * Description: Interface to the Entity Component System
 */

#pragma once

#include "Common.h"
#include "EntityStore.h"
#include "ComponentStore.h"
#include "Systems.h"

namespace ecs {

    EntityId getNewEntityId(const std::string &tag = "") {
        static EntityId entityId = 0;
        // TODO: create new entity in EntityStore
        //  and pass entityName for lookup table in EntityStore
        entity::EntityStore::getInstance()->addEntity(entityId, tag);
        return entityId;
    }

    void rmEntity(EntityId entityID);

    template<typename T>
    void addComponent(EntityId entityId, T &component) {
        component.entityID = entityId;
        component::ComponentStore *componentStore = component::ComponentStore::getInstance();
        entity::EntityStore *entityStore = entity::EntityStore::getInstance();

        T *componentPtr = componentStore->addComponent<T>(component);

        if (componentPtr)
            entityStore->addComponent(entityId, T::ID(), componentPtr);
    }

    void registerSystem(SystemFunctionPtr callback, int priority = 1) {
        // TODO: add the callback to the systems with priority
    }

    void run() {
        // TODO: run the systems in order of priority
    }

    template<typename T>
    void rmComponent(ComponentId &name);

    template<typename T>
    T *getComponent(EntityId entityID, ComponentId &name);

    template<typename T>
    void activateComponent(EntityId entityID, ComponentId &name);

    template<typename T>
    void deactivateComponent(EntityId entityID, ComponentId &name);

// void addSystem(void (funcPtr)(void));
// void rmSystem(void (funcPtr)(void));
// void enableSystem(void (funcPtr)(void));
// void disableSystem(void (funcPtr)(void));

    template<typename T>
    T *getComponentList() {
        component::ComponentStore::getInstance()->getComponentList()
    }

    int *getEntityList(ComponentId *componentTuple);
// TODO: get ComponentList with list of entity IDs

};
