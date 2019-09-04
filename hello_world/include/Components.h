//
// Created by Garrett Bellomy on 2019-09-04.
//

#ifndef ECS_EXAMPLES_COMPONENTS_H
#define ECS_EXAMPLES_COMPONENTS_H

#include "Common.h"

struct MessageComponent {
    const static UINT MESSAGE_COMPONENT_ID = 0x1;
    UINT entity_id;
    bool active;
    const char* message;
    unsigned short len;
};

struct TestComponent {
    const static UINT MESSAGE_COMPONENT_ID = 0x1;
    UINT entity_id;
    bool active;
    const char* message;
    unsigned short len;
};

#endif //ECS_EXAMPLES_COMPONENTS_H
