/* Author: GarRaptor
 * Description: Interface to the Entity Component System
 */

#pragma once

#include "Common.h"

namespace ecs {
    namespace system {

        class Systems {
            bool stop_;
            std::map<SystemRunType, std::vector<SystemFunctionPtr>> systems_;

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

            void run() {
                _runAll(OnInit);
                _runAll(OnStart);
                while(!stop_) {
                    _runAll(OnTick);
                    _runAll(OnLateTick);
                }
                _runAll(OnCleanup);
                stop_ = false;
            }

            void stop() {
                stop_ = true;
            }

        private:
            void _runAll(SystemRunType systemRunType) {
                for (size_t i = 0; i < systems_[systemRunType].size(); i++) {
                    systems_[systemRunType][i]();
                }
            }
        };

    };
};
