/* Author: GarRaptor
 * Description: holds a map of ComponentList containers. Goal is to be able to define a component
 *   and to store it in this structure for access by user-defined systems.
 * Notes:
 *  - must be destroyed by calling the rmComponentList for each ComponentList
 */

#pragma once

#include <iostream>
#include <map>
#include <string>

#include "ComponentList.h"
#include "Common.h"

typedef std::map<std::string, ecs::component::ComponentList> ComponentsMap;

namespace ecs {
    namespace component {

        class ComponentStore {
            ComponentsMap componentsMap_;

        public:

            static ComponentStore *getInstance() {
                static ComponentStore *instance = new ComponentStore();
                return instance;
            }


            bool addComponentList(ComponentId &componentId) {
                if (isComponentList(componentId))
                    return false;

                componentsMap_[componentId];
                return true;
            }

            template<typename T>
            T *getComponentList() {
                ComponentList *componentList = _getComponentList(T::ID());

                if (!componentList)
                    return nullptr;

                return componentList->get<T>();
            }

            template<typename T>
            void rmComponentList(ComponentId &componentId) {
                ComponentList *componentList = _getComponentList(componentId);

                if (!componentList)
                    return;

                componentList->destroy<T>();
                _rmComponentList(componentId);
            }

            template<typename T>
            T *addComponent(const T &component) {
                ComponentList *componentList = _getComponentList(T::ID());

                if (!componentList) {
                    if (!addComponentList(T::ID()))
                        return nullptr;

                    componentList = _getComponentList(T::ID());
                    if (!componentList)
                        return nullptr;
                }

                return componentList->append<T>(component);
            }

            template<typename T>
            T *getComponent(ComponentId &componentId, EntityId entityID) {
                ComponentList *componentList = _getComponentList(componentId);

                if (!componentList)
                    return nullptr;

                return componentList->get<T>(entityID);
            }

            template<typename T>
            bool rmComponent(ComponentId &componentId, EntityId entityID) {
                ComponentList *componentList = _getComponentList(componentId);

                if (!componentList)
                    return false;

                componentList->remove<T>(entityID);
                return true;
            }

            template<typename T>
            bool deactivateComponent(ComponentId &componentId, EntityId entityID) {
                ComponentList *componentList = _getComponentList(componentId);

                if (!componentList)
                    return false;

                componentList->deactivate<T>(entityID);
                return true;
            }

            template<typename T>
            bool activateComponent(ComponentId &componentId, EntityId entityID) {
                ComponentList *componentList = _getComponentList(componentId);

                if (!componentList)
                    return false;

                componentList->activate<T>(entityID);
                return true;
            }


            template<typename T>
            int size(ComponentId &componentId) const {
                ComponentList *componentList = _getComponentList(componentId);

                if (!componentList)
                    return -1;

                return componentList->size();
            }

            int active(ComponentId &componentId) const {
                ComponentList *componentList = _getComponentList(componentId);

                if (!componentList)
                    return -1;

                return componentList->active();
            }

            bool isActive(ComponentId &componentId, EntityId entityID) const {
                return (componentsMap_.find(componentId)->second).isActive(entityID);
            }

            bool isComponentList(ComponentId &componentId) const {
                return (componentsMap_.find(componentId) != componentsMap_.end());
            }

        private:

            ComponentStore() :
                    componentsMap_() {}

            ComponentStore(const ComponentStore &) = delete;

            ComponentStore(const ComponentStore &&) = delete;

            ComponentStore &operator=(const ComponentStore &) = delete;

            ComponentStore &operator=(const ComponentStore &&) = delete;


            ComponentList *_getComponentList(ComponentId &componentId) const {
                if (!isComponentList(componentId))
                    return nullptr;

                return const_cast<ComponentList *>(&(componentsMap_.find(componentId)->second));
            }

            void _rmComponentList(ComponentId &componentId) {
                if (!isComponentList(componentId))
                    return;

                componentsMap_.erase(componentId);
            }
        };
    };
};
