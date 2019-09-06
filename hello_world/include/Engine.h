//
// Created by Garrett Bellomy on 2019-09-04.
//

#ifndef ECS_EXAMPLES_ENGINE_H
#define ECS_EXAMPLES_ENGINE_H

#include "Common.h"

struct ComponentList {
    UINT id;
    USHORT active;
    std::map<UINT, USHORT> indexMap;
    void* components;
};


// Contains the systems and order to run
class Engine {
    typedef void (*sysFunc)(Engine&);

    std::map<USHORT, ComponentList> _ComponentLists;
    sysFunc* _Systems;

    Engine() = delete;

public:
    // add system(sysID, priorityLevel, func) - func needs to return void and take Engine& as arg
    // remove system(sysID) - remove func by sysID
    // get component by entity(CL_ID, entityID)
    // remove component by entity(CL_ID, entityID)

    // add component(CL_ID, comp) - CL_ID to get CL then CL.add(comp)
    template <typename T>
    void addComponent(UINT compListID, void* component)
    {
        ComponentList& compList =  _ComponentLists[compListID];
        if (!compList.components)
        {
            T* tempComponents = new T[64];
            compList.components = reinterpret_cast<void*>(tempComponents);
        }

        // cast from void* to a T* array
        T* tComponents = reinterpret_cast<T*>(compList.components);
        // cast from a void* to a T*, that points to the component to add
        T* tComponentPtr = reinterpret_cast<T*>(component);

        // add component to array
        tComponents[compList.active] = *tComponent;
        compList.active++;
    }
};

#endif //ECS_EXAMPLES_ENGINE_H
