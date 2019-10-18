/* Author: GarRaptor
 * Description: holds a map of component_vector containers. Goal is to be able to define a component
 *   and to store it in this structure for access by user-defined systems.
 * Uses:
 *   ComponentStore* cs = ComponentStore::getInstance(); // uses the singleton pattern
 *   cs->addComponent<T>(component); // if this is a new type will create a new component vector.
 *   cs->getComponentList<T>(name); // return a list of components of type T
 *   cs->rmComponentList<T>(name); // TODO
 *   cs->getComponent<T>(name, entityID); // return a component of type T for a particular entityID.
 *   cs->rmComponent<T>(name, entityID); // TODO
 *   cs->size<T>(name); // return the number of components in a component_vector
 *   cs->active<T>(name); // return the number of active components in a component_vector
 *   cs->isActive<T>(name, entityID); // return if the component is active with entityID
 *   cs->isComponent(name); // verify that component_vector name already exists
 */

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utils.h"
#include "component_vector.h"

typedef std::map<std::string, component_vector> components_map;

class ComponentStore {
    components_map componentsMap_;

    ComponentStore():
      componentsMap_()
    {}

    ComponentStore(const ComponentStore&) = delete;
    ComponentStore(const ComponentStore&&) = delete;
    ComponentStore& operator= (const ComponentStore&) = delete;
    ComponentStore& operator= (const ComponentStore&&) = delete;

public:
    static ComponentStore* getInstance()
    {
        static ComponentStore* instance = new ComponentStore();
        return instance;
    }

public:
    template <typename T>
    void addComponent(const T& component)
    {
        component_vector* componentVector = _getComponents(component.name);
        if (!componentVector)
        {
            componentsMap_[component.name];
            componentVector = _getComponents(component.name);
        }

        componentVector->append<T>(component);
    }

    template <typename T>
    T* getComponentList(const std::string& name)
    {
        component_vector* componentVector = _getComponents(name);

        if (!componentVector)
            return nullptr;

        return componentVector->get<T>();
    }

    template <typename T>
    T* getComponent(const std::string& name, int entityID)
    {
        component_vector* componentVector = _getComponents(name);

        if (!componentVector)
            return nullptr;

        return componentVector->get<T>(entityID);
    }

    template <typename T>
    int size(const std::string& name)
    {
        component_vector* componentVector = _getComponents(name);

        if (!componentVector)
            return -1;

        return componentVector->size();
    }

    template <typename T>
    int active(const std::string& name)
    {
        component_vector* componentVector = _getComponents(name);

        if (!componentVector)
            return -1;

        return componentVector->active();
    }

    bool isActive(const std::string& name, int entityID)
    {
        return componentsMap_[name].isActive(entityID);
    }

    // TODO: figure out if this has any usefulness???
    /*void getComponentNames(std::string*& buffer, int size)
    {
        if (size < this->size())
            return;

        components_map::iterator it = componentsMap_.begin();
        for (int i = 0; it != componentsMap_.end(); ++it, ++i)
        {
            buffer[i] = it->first;
        }
    }*/

    bool isComponent(const std::string& name) const
    {
        return (componentsMap_.find(name) != componentsMap_.end());
    }

private:
    component_vector* _getComponents(const std::string& name)
    {
        if (isComponent(name))
        {
            return &componentsMap_[name];
        }
        return nullptr;
    }
};
