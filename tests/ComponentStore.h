/* Author: GarRaptor
 * Description: holds a map of component_list containers. Goal is to be able to define a component
 *   and to store it in this structure for access by user-defined systems.
 */

#pragma once

#include <iostream>
#include <map>
#include <string>

#include "utils.h"
#include "component_list.h"

typedef std::map<std::string, component_list> components_map;

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
    bool addComponentList(const std::string& name);

    template <typename T>
    T* getComponentList(const std::string& name);

    // TODO
    // template <typename T>
    // void rmComponentList<T>(const std::string& name);

    template <typename T>
    bool addComponent(const T& component);

    template <typename T>
    T* getComponent(const std::string& name, int entityID);

    // TODO
    // template <typename T>
    // void rmComponent<T>(const std::string& name, int entityID);

    // TODO
    // template <typename T>
    // void deactivateComponent<T>(const std::string& name, int entityID);

    // TODO
    // template <typename T>
    // void activateComponent<T>(const std::string& name, int entityID);

public: // accessor functions

    template <typename T>
    int size(const std::string& name);

    template <typename T>
    int active(const std::string& name);

    bool isActive(const std::string& name, int entityID);

    // TODO: figure out if this has any usefulness???
    //void getComponentNames(std::string*& buffer, int size);

    bool isComponentList(const std::string& name) const;

private: // helper functions
    component_list* _getComponents(const std::string& name);
};

// PUBLIC

bool ComponentStore::addComponentList(const std::string& name)
{
    if (isComponentList(name))
        return false;

    componentsMap_[name];
    return true;
}

template <typename T>
T* ComponentStore::getComponentList(const std::string& name)
{
    component_list* componentVector = _getComponents(name);

    if (!componentVector)
        return nullptr;

    return componentVector->get<T>();
}

// TODO
// template <typename T>
// void ComponentStore::rmComponentList<T>(const std::string& name);

template <typename T>
bool ComponentStore::addComponent(const T& component)
{
    component_list* componentVector = _getComponents(component.name);

    if (!componentVector)
        return false;

    componentVector->append<T>(component);
    return true;
}

template <typename T>
T* ComponentStore::getComponent(const std::string& name, int entityID)
{
    component_list* componentVector = _getComponents(name);

    if (!componentVector)
        return nullptr;

    return componentVector->get<T>(entityID);
}

// TODO
// template <typename T>
// void rmComponent<T>(const std::string& name, int entityID);

// TODO
// template <typename T>
// void deactivateComponent<T>(const std::string& name, int entityID);

// TODO
// template <typename T>
// void activateComponent<T>(const std::string& name, int entityID);

// PUBLIC - accessor functions

template <typename T>
int ComponentStore::size(const std::string& name)
{
    component_list* componentVector = _getComponents(name);

    if (!componentVector)
        return -1;

    return componentVector->size();
}

template <typename T>
int ComponentStore::active(const std::string& name)
{
    component_list* componentVector = _getComponents(name);

    if (!componentVector)
        return -1;

    return componentVector->active();
}

bool ComponentStore::isActive(const std::string& name, int entityID)
{
    return componentsMap_[name].isActive(entityID);
}

// TODO: figure out if this has any usefulness???
/*void ComponentStore::getComponentNames(std::string*& buffer, int size)
{
    if (size < this->size())
        return;

    components_map::iterator it = componentsMap_.begin();
    for (int i = 0; it != componentsMap_.end(); ++it, ++i)
    {
        buffer[i] = it->first;
    }
}*/

bool ComponentStore::isComponentList(const std::string& name) const
{
    return (componentsMap_.find(name) != componentsMap_.end());
}


// PRIVATE - helper functions

component_list* ComponentStore::_getComponents(const std::string& name)
{
    if (isComponentList(name))
    {
        return &componentsMap_[name];
    }
    return nullptr;
}
