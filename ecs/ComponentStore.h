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

            static ComponentStore* getInstance()
            {
                static ComponentStore* instance = new ComponentStore();
                return instance;
            }


            bool addComponentList(ComponentId& name);

            template <typename T>
            T* getComponentList(ComponentId& name);

            template <typename T>
            void rmComponentList(ComponentId& name);

            template <typename T>
            bool addComponent(const T& component);

            template <typename T>
            T* getComponent(ComponentId& name, EntityId entityID);

            template <typename T>
            bool rmComponent(ComponentId& name, EntityId entityID);

            template <typename T>
            bool deactivateComponent(ComponentId& name, EntityId entityID);

            template <typename T>
            bool activateComponent(ComponentId& name, EntityId entityID);


            template <typename T>
            int size(ComponentId& name) const;

            template <typename T>
            int active(ComponentId& name) const;

            bool isActive(ComponentId& name, EntityId entityID) const;

            bool isComponentList(ComponentId& name) const;

        private:

            ComponentStore():
                    componentsMap_()
            {}

            ComponentStore(const ComponentStore&) = delete;
            ComponentStore(const ComponentStore&&) = delete;
            ComponentStore& operator= (const ComponentStore&) = delete;
            ComponentStore& operator= (const ComponentStore&&) = delete;


            ComponentList* _getComponentList(ComponentId& name) const;

            void _rmComponentList(ComponentId& name);
        };


// PUBLIC MODIFYING FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool ComponentStore::addComponentList(ComponentId& name)
        {
            if (isComponentList(name))
                return false;

            componentsMap_[name];
            return true;
        }

        template <typename T>
        T* ComponentStore::getComponentList(ComponentId& name)
        {
            ComponentList* componentList = _getComponentList(name);

            if (!componentList)
                return nullptr;

            return componentList->get<T>();
        }

        template <typename T>
        void ComponentStore::rmComponentList(ComponentId& name)
        {
            ComponentList* componentList = _getComponentList(name);

            if (!componentList)
                return;

            componentList->destroy<T>();
            _rmComponentList(name);
        }

        template <typename T>
        bool ComponentStore::addComponent(const T& component)
        {
            ComponentList* componentList = _getComponentList(component.name);

            if (!componentList)
            {
                if (!addComponentList(component.name))
                    return false;

                ComponentList* componentList = _getComponentList(component.name);
                if (!componentList)
                    return false;
            }

            componentList->append<T>(component);
            return true;
        }

        template <typename T>
        T* ComponentStore::getComponent(ComponentId& name, EntityId entityID)
        {
            ComponentList* componentList = _getComponentList(name);

            if (!componentList)
                return nullptr;

            return componentList->get<T>(entityID);
        }

        template <typename T>
        bool ComponentStore::rmComponent(ComponentId& name, EntityId entityID)
        {
            ComponentList* componentList = _getComponentList(name);

            if (!componentList)
                return false;

            componentList->remove<T>(entityID);
            return true;
        }

        template <typename T>
        bool ComponentStore::activateComponent(ComponentId& name, EntityId entityID)
        {
            ComponentList* componentList = _getComponentList(name);

            if (!componentList)
                return false;

            componentList->activate<T>(entityID);
            return true;
        }

        template <typename T>
        bool ComponentStore::deactivateComponent(ComponentId& name, EntityId entityID)
        {
            ComponentList* componentList = _getComponentList(name);

            if (!componentList)
                return false;

            componentList->deactivate<T>(entityID);
            return true;
        }

// PUBLIC ACCESSOR FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        template <typename T>
        int ComponentStore::size(ComponentId& name) const
        {
            ComponentList* componentList = _getComponentList(name);

            if (!componentList)
                return -1;

            return componentList->size();
        }

        template <typename T>
        int ComponentStore::active(ComponentId& name) const
        {
            ComponentList* componentList = _getComponentList(name);

            if (!componentList)
                return -1;

            return componentList->active();
        }

        bool ComponentStore::isActive(ComponentId& name, EntityId entityID) const
        {
            return (componentsMap_.find(name)->second).isActive(entityID);
        }

        bool ComponentStore::isComponentList(ComponentId& name) const
        {
            return (componentsMap_.find(name) != componentsMap_.end());
        }


// PRIVATE HELPER FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        ComponentList* ComponentStore::_getComponentList(ComponentId& name) const
        {
            if (!isComponentList(name))
                return nullptr;

            return const_cast<ComponentList*>(&(componentsMap_.find(name)->second));
        }

        void ComponentStore::_rmComponentList(ComponentId& name)
        {
            if (!isComponentList(name))
                return;

            componentsMap_.erase(name);
        }

    };
};
