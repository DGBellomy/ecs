//
// Created by Garrett Bellomy on 2/5/2020.
// Description: Holds common defines and typedefs needed throughout the ecs headers and possibly by end-user.
//

#pragma once

#include <string>
#include <map>
#include <vector>

#define Component(comp, compData) \
    struct comp {\
        static std::string ID() { return #comp; };\
        EntityId entityID;\
        struct \
            compData data;\
    };

#define StaticComponent(comp, data) \
    struct static_##comp data;\
    static static_##comp comp;

#define forEachComponent(component, ComponentType, process) \
{\
    ComponentType * list_##component = ecs::Components::get<ComponentType>();\
    const int active_##component = ecs::Components::active(ComponentType::ID());\
    ComponentType * component = &list_##component[0];\
    for (int i = 0; i < active_##component; component = &list_##component[++i])\
    {\
      process\
    }\
}

typedef int EntityId;
typedef const std::string ComponentId;

typedef void (*SystemFunctionPtr)();

enum SystemRunType {
    OnInit,
    OnStart,
    OnTick,
    OnLateTick,
    OnCleanup
};
