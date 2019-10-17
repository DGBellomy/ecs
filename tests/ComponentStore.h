/* Author: GarRaptor
 * Description: ... TODO: add something here
 * Uses:
 *   ... TODO: add something here
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
    components_map m_ComponentsMap;

    ComponentStore():
      m_ComponentsMap()
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
            m_ComponentsMap[component.name];
            componentVector = _getComponents(component.name);
        }

        componentVector->push<T>(component);
    }

    template <typename T>
    T* getComponents(const std::string& name)
    {
        component_vector* componentVector = _getComponents(name);
        if (!componentVector)
        {
            return nullptr;
        }

        return componentVector->get<T>();
    }

    int size()
    {
        return m_ComponentsMap.size();
    }

    template <typename T>
    int size(const std::string& name)
    {
        // TODO: define this
    }

    void getComponentNames(std::string*& buffer, int size)
    {
        if (size < this->size())
        {
            return;
        }

        components_map::iterator it = m_ComponentsMap.begin();
        for (int i = 0; it != m_ComponentsMap.end(); ++it, ++i)
        {
            buffer[i] = it->first;
        }
    }

    bool isComponent(const std::string& name) const
    {
        return (m_ComponentsMap.find(name) != m_ComponentsMap.end());
    }

private:
    component_vector* _getComponents(const std::string& name)
    {
        if (isComponent(name))
        {
            return &m_ComponentsMap[name];
        }
        return nullptr;
    }
};
