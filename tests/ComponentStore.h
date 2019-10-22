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

public: // constructors

    static ComponentStore* getInstance()
    {
        static ComponentStore* instance = new ComponentStore();
        return instance;
    }

public: // modifying functions

    bool addComponentList(const std::string& name);
    template <typename T> T* getComponentList(const std::string& name);
    template <typename T> void rmComponentList(const std::string& name);
    template <typename T> bool addComponent(const T& component);
    template <typename T> T* getComponent(const std::string& name, int entityID);
    template <typename T> bool rmComponent(const std::string& name, int entityID);
    template <typename T> bool deactivateComponent(const std::string& name, int entityID);
    template <typename T> bool activateComponent(const std::string& name, int entityID);

public: // accessor functions

    template <typename T> int size(const std::string& name) const;
    template <typename T> int active(const std::string& name) const;
    bool isActive(const std::string& name, int entityID) const;
    bool isComponentList(const std::string& name) const;

    // TODO: figure out if this has any usefulness???
    //void getComponentNames(std::string*& buffer, int size);

private: // helper functions

    component_list* _getComponentList(const std::string& name);
};


// PUBLIC MODIFYING FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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
    component_list* componentList = _getComponentList(name);

    if (!componentList)
        return nullptr;

    return componentList->get<T>();
}

template <typename T>
void ComponentStore::rmComponentList(const std::string& name)
{
    component_list* componentList = _getComponentList(name);

    if (!componentList)
        return;

    componentList->destroy<T>();
    _rmComponentList(name);
}

template <typename T>
bool ComponentStore::addComponent(const T& component)
{
    component_list* componentList = _getComponentList(component.name);

    if (!componentList)
        return false;

    componentList->append<T>(component);
    return true;
}

template <typename T>
T* ComponentStore::getComponent(const std::string& name, int entityID)
{
    component_list* componentList = _getComponentList(name);

    if (!componentList)
        return nullptr;

    return componentList->get<T>(entityID);
}

template <typename T>
bool rmComponent(const std::string& name, int entityID)
{
    component_list* componentList = _getComponentList(name);

    if (!componentList)
        return false;

    componentList->remove<T>(entityID);
    return true;
}

template <typename T>
bool activateComponent(const std::string& name, int entityID)
{
    component_list* componentList = _getComponentList(component.name);

    if (!componentList)
        return false;

    componentList->activate<T>(entityID);
    return true;
}

template <typename T>
bool deactivateComponent(const std::string& name, int entityID)
{
    component_list* componentList = _getComponentList(component.name);

    if (!componentList)
        return false;

    componentList->deactivate<T>(entityID);
    return true;
}

// PUBLIC ACCESSOR FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename T>
int ComponentStore::size(const std::string& name) const
{
    component_list* componentList = _getComponentList(name);

    if (!componentList)
        return -1;

    return componentList->size();
}

template <typename T>
int ComponentStore::active(const std::string& name) const
{
    component_list* componentList = _getComponentList(name);

    if (!componentList)
        return -1;

    return componentList->active();
}

bool ComponentStore::isActive(const std::string& name, int entityID) const
{
    return componentsMap_[name].isActive(entityID);
}

bool ComponentStore::isComponentList(const std::string& name) const
{
    return (componentsMap_.find(name) != componentsMap_.end());
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


// PRIVATE HELPER FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

component_list* ComponentStore::_getComponentList(const std::string& name)
{
    if (isComponentList(name))
    {
        return &componentsMap_[name];
    }
    return nullptr;
}

component_list* ComponentStore::_rmComponentList(const std::string& name)
{
    if (!isComponentList(name))
        return;

    componentsMap_.erase(name);
}
