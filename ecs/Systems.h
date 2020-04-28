/* Author: GarRaptor
 * Description: Interface to the Entity Component System
 */

#pragma once

#include "Types.h"

namespace ecs {
    namespace system {

        class Systems {
            bool stop_;
            std::map<SystemRunType, std::vector<SystemFunctionPtr> > systems_;

        public:
            static Systems *getInstance() {
                static Systems *instance = new Systems();
                return instance;
            }

            void addSystem(SystemFunctionPtr systemFunctionPtr, SystemRunType systemRunType) {
                if (systems_.find(systemRunType) == systems_.end()) {
                    systems_[systemRunType];
                }

                systems_[systemRunType].push_back(systemFunctionPtr);
            }

            void run(SystemRunType systemRunType) {
                for (size_t i = 0; i < systems_[systemRunType].size(); i++) {
                    systems_[systemRunType][i]();
                }
            }
        };

    };
};
