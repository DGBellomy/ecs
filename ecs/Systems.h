/* Author: GarRaptor
 * Description: Interface to the Entity Component System
 */

#pragma once

#include "Common.h"

namespace ecs {
    namespace system {

        class Systems {
            std::vector<SystemFunctionPtr> systems_;

        public:
            static Systems *getInstance() {
                static Systems *instance = new Systems();
                return instance;
            }

            void addSystem(SystemFunctionPtr systemFunctionPtr) {
                systems_.push_back(systemFunctionPtr);
            }
        };

    };
};
