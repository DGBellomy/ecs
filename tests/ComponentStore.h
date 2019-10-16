#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utils.h"

typedef void* component_list;
typedef std::map<std::string, component_list> component_list_map;

class ComponentStore {
    component_list_map m_ComponentListMap;

public:
    static ComponentStore* getInstance()
    {
        static ComponentStore* instance = new ComponentStore();
        return instance;
    }

    std::vector<std::string> getComponentNames()
    {
        std::vector<std::string> componentNames(m_ComponentListMap.size());
        for (component_list_map::iterator it = m_ComponentListMap.begin(); it != m_ComponentListMap.end(); ++it)
        {
            componentNames.push_back(it->first);
        }
        return componentNames;
    }

    template <typename T>
    void addComponent(const T& component)
    {
        component_list* componentList = _getComponentList(component.name);
        if (!componentList)
        {
            T* newcomponentList = new T[16];
            m_ComponentListMap[component.name] = reinterpret_cast<void*>(newcomponentList);
            componentList = _getComponentList(component.name);
        }

        // FIXME: change 0 to the next available position
        T* castedComponentList = reinterpret_cast<T*>(*componentList);
        castedComponentList[0] = component;
        *componentList = reinterpret_cast<T*>(castedComponentList);
    }

    template <typename T>
    T* getComponentList(const std::string& name)
    {
        component_list* componentList = _getComponentList(name);
        if (!componentList)
        {
            return nullptr;
        }

        T* castedComponentList = reinterpret_cast<T*>(*componentList);
        // FIXME: 16 is hard set and needs to be moved
        return castedComponentList;
    }

private:

    bool _isComponentList(const std::string& name) const
    {
        return (m_ComponentListMap.find(name) != m_ComponentListMap.end());
    }

    component_list* _getComponentList(const std::string& name)
    {
        if (_isComponentList(name))
        {
            return &m_ComponentListMap[name];
        }
        return nullptr;
    }
};
