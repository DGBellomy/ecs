//
// Created by Garrett Bellomy on 2/5/2020.
// Description: Holds common defines and typedefs needed throughout the coreECS headers and possibly by end-user.
//

#ifndef ECS_EXAMPLES_COMMON_H
#define ECS_EXAMPLES_COMMON_H

#include <string>
#include <map>
#include <vector>

#define Component(comp, compData) \
    struct comp {\
        static std::string ID() { return #comp; };\
        EntityId entityID;\
        struct \
            compData data;\
        \
    };

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

#endif //ECS_EXAMPLES_COMMON_H
