/* Author: GarRaptor
 * Description: Interface to the Entity Component System
 */

#pragma once

#include "Common.h"

namespace ecs {
    namespace system {

        class Systems {
            std::vector<SystemFunctionPtr> systems_;
        };

    };
};
