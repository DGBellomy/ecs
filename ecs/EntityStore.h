/* Author: GarRaptor
 * Description: Keep track of Entities
 *   stores a list of component names associated with an entity.
 */

#pragma once

#include "Common.h"

namespace ecs {
    namespace entity {

        class EntityStore {
            static EntityId ID_;
            std::map<EntityId, std::vector<std::string>> entities_;

        public:
            static EntityStore* getInstance()
            {
                static EntityStore* instance = new EntityStore();
                return instance;
            }

            static EntityId getID()
            {
                static EntityId id = 0;
                ID_ = id++;
                return ID_;
            }


            void addEntity(EntityId entityID)
            {
                // TODO: why do I short circuit if entityID is not found in entities_ ???
                if (entities_.find(entityID) == entities_.end())
                    return;

                entities_[ID_];
            }

            void rmEntity(EntityId entityID)
            {
                if (entities_.find(entityID) == entities_.end())
                    return;
                // TODO: remove entityID
            }

            void addComponent(ComponentId& componentId)
            {
                entities_[ID_].push_back(componentId);
            }

            void rmComponent(EntityId entityID, ComponentId& ComponentId)
            {
                // TODO: define
            }

            std::vector<std::string> getComponents(EntityId entityID)
            {
                return entities_[entityID];
            }
        };

        EntityId EntityStore::ID_ = 0;

    };
};
