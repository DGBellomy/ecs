/* Author: GarRaptor
 * Description: Interface to the Entity Component System
 */

#pragma once

#include "Types.h"
#include "EntityStore.h"
#include "ComponentStore.h"
#include "Systems.h"

namespace ecs {

    class Entity {
        EntityId id_;

    public:
        Entity(const Entity &) = delete;

        Entity(const Entity &&) = delete;

        Entity &operator=(const Entity &) = delete;

        Entity &operator=(const Entity &&) = delete;

    public:
        Entity(const std::string tag = "") {
            static EntityId entityId = 0;
            entity::EntityStore::getInstance()->addEntity(entityId, tag);
            this->id_ = entityId++;
        }

        template<typename T>
        void addComponent(T &component) {
            component.entityID = this->id_;
            component::ComponentStore *componentStore = component::ComponentStore::getInstance();
            entity::EntityStore *entityStore = entity::EntityStore::getInstance();

            T *componentPtr = componentStore->addComponent<T>(component);

            if (componentPtr)
                entityStore->addComponent(this->id_, T::ID(), componentPtr);
        }

        void rmEntity(EntityId entityID) {
            // TODO: remove entity
        }
    };

    class Components {
    StaticClass(Components)

    public:
        static size_t active(const ComponentId &componentId) {
            return component::ComponentStore::getInstance()->active(componentId);
        }

        template<typename T>
        static void destroy(ComponentId &name) {
            // TODO: define
        }

        template<typename T>
        static T *get() {
            return component::ComponentStore::getInstance()->getComponentList<T>();
        }

        template<typename T>
        static T *get(EntityId entityID) {
            return reinterpret_cast<T *>(entity::EntityStore::getInstance()->getComponent(entityID, T::ID()));
        }

        template<typename T>
        static void activate(EntityId entityID, ComponentId &name) {
            // TODO: define
        }

        template<typename T>
        static void deactivate(EntityId entityID, ComponentId &name) {
            // TODO: define
        }
    };

    class Systems {
    StaticClass(Systems)

    public:
        static void onInit(SystemFunctionPtr callback) {
            system::Systems::getInstance()->addSystem(callback, OnInit);
        }

        static void onSetup(SystemFunctionPtr callback) {
            system::Systems::getInstance()->addSystem(callback, OnSetup);
        }

        static void onTick(SystemFunctionPtr callback) {
            system::Systems::getInstance()->addSystem(callback, OnTick);
        }

        static void onLateTick(SystemFunctionPtr callback) {
            system::Systems::getInstance()->addSystem(callback, OnLateTick);
        }

        static void onCleanup(SystemFunctionPtr callback) {
            system::Systems::getInstance()->addSystem(callback, OnCleanup);
        }

        // void rmSystem(void (funcPtr)(void));
        // void enableSystem(void (funcPtr)(void));
        // void disableSystem(void (funcPtr)(void));

        static void run(SystemRunType systemRunType) {
            system::Systems::getInstance()->run(systemRunType);
        }
    };


//    int *getEntityList(ComponentId *componentTuple);
// TODO: get ComponentList with list of entity IDs

};
