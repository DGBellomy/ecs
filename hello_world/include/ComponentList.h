//
// Created by Garrett Bellomy on 2019-09-04.
//

#ifndef ECS_EXAMPLES_COMPONENTLIST_H
#define ECS_EXAMPLES_COMPONENTLIST_H

#include "Common.h"

// holds a compact list of components of a specific type
// contains a hash map to quickly access a component by entity_id
template <typename T>
class ComponentList {
    static ComponentList<T>* _instance;

    USHORT _active; // number of active components
    USHORT _size; // size of container
    T* _componentList; // compact list of active components
    std::map<UINT, USHORT> _idMap; // map entity_id to index in compact list for quick lookup

public:
    static ComponentList<T>* instance()
    {
        if (_instance == nullptr)
        {
            _instance = new ComponentList<T>();
            _instance->_size = 64;
            _instance->_active = 0;
            _instance->_componentList = new T[_instance->_size];
        }
        return _instance;
    }

    // get a component by entity_id
    T* get(UINT entity_id)
    {
        USHORT index = _idMap[entity_id];
        return &_componentList[index];
    }

    // get the entire compact component list (for read or write?)
    T* get()
    {
        return _componentList;
    }

    // add a component to the list and to the mapper
    void add(T component)
    {
        if (_active < _size)
        {
            _componentList[_active] = component;
            _idMap[component.entity_id] = _active;
            _active++;
        }
        else
        {
            // resize
        }
    }

    // remove a component from the list and mapper
    void remove(UINT entity_id)
    {
        USHORT index = _idMap[entity_id];
        _componentList[index] = _componentList[_active];
        _idMap.erase(entity_id);
        _active--;
    }

    // disable a compoent in the list and update mapper
    void disable(UINT entity_id)
    {
        USHORT index = _idMap[entity_id];
        T component = _componentList[index];
        component.active = false;
    }

    // enable a component in the list and update mapper
    void enable(UINT entity_id)
    {
        USHORT index = _idMap[entity_id];
        T component = _componentList[index];
        component.active = true;
    }

    USHORT active()
    {
        return _active;
    }
};

#endif //ECS_EXAMPLES_COMPONENTLIST_H
