//
// Created by Garrett Bellomy on 2/5/2020.
// Description: Holds common defines and typedefs needed throughout the ECS headers and possibly by end-user.
//

#ifndef ECS_EXAMPLES_COMMON_H
#define ECS_EXAMPLES_COMMON_H

#include <string>
#include <map>
#include <vector>

#define Component(comp, data) \
    struct comp {\
        data\
        static ComponentId name;\
        EntityId entityID;\
    };\
    ComponentId comp::name = #comp

typedef int EntityId;
typedef const std::string ComponentId;
typedef void (*SystemFunctionPtr)(void);

#endif //ECS_EXAMPLES_COMMON_H
