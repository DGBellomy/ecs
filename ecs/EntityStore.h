/* Author: GarRaptor
 * Description: Keep track of Entities
 *   stores a list of component names associated with an entity.
 */

#pragma once

#include "Common.h"

namespace ecs {
    namespace entity {

        class EntityStore {
            static int ID_ = 0;
            std::map<EntityId, std::vector<std::string>> entities_;

        public:
            static EntityStore* getInstance()
            {
                static EntityStore* instance = new EntityStore();
                return instance;
            }

            static int getID()
            {
                return ID_;
            }


            void addEntity(int entityID)
            {
                // TODO: why do I short circuit if entityID is not found in entities_ ???
                if (entities_.find(entityID) == entities_.end())
                    return;

                entities_[ID_];
            }

            void rmEntity(int entityID)
            {
                if (entities_.find(entityID) == entities_.end())
                    return;
                // TODO: remove entityID
            }

            void addComponent(const std::string& name)
            {
                entities_[ID_].push_back(name);
            }

            void rmComponent(int entityID, const std::string& name)
            {
                // TODO: define
            }

            std::vector<std::string> getComponents(int entityID)
            {
                return entities_[entityID];
            }
        };

    };
};
