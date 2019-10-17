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

public:
    static ComponentStore* getInstance()
    {
        static ComponentStore* instance = new ComponentStore();
        return instance;
    }

    std::vector<std::string> getComponentNames()
    {
        std::vector<std::string> componentNames(m_ComponentsMap.size());
        for (components_map::iterator it = m_ComponentsMap.begin(); it != m_ComponentsMap.end(); ++it)
        {
            componentNames.push_back(it->first);
        }
        return componentNames;
    }

    template <typename T>
    void addComponent(const T& component)
    {
        component_vector* componentVector = _getComponents(component.name);
        if (!componentVector)
        {
            component_vector newComponentVector;
            m_ComponentsMap[component.name] = newComponentVector;
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

private:

    bool _isComponent(const std::string& name) const
    {
        return (m_ComponentsMap.find(name) != m_ComponentsMap.end());
    }

    component_vector* _getComponents(const std::string& name)
    {
        if (_isComponent(name))
        {
            return &m_ComponentsMap[name];
        }
        return nullptr;
    }
};
