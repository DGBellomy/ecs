/* Author: GarRaptor
 * Description: Keep track of Entities
 *   stores a list of component names associated with an entity.
 */

#pragma once

#include "Common.h"

typedef std::map<ComponentId, void*> ComponentPtrMap;
typedef std::map<EntityId, ComponentPtrMap> EntityMap;

namespace ecs {
    namespace entity {

        class EntityStore {
            EntityMap entities_;

        public:
            static EntityStore* getInstance()
            {
                static EntityStore* instance = new EntityStore();
                return instance;
            }

            void addEntity(EntityId entityID)
            {
                // TODO: why do I short circuit if entityID is not found in entities_ ???
                if (entities_.find(entityID) == entities_.end())
                    return;
                // TODO: if entity does not exist, then add entityID to data structure

                entities_[entityID];
            }

            void rmEntity(EntityId entityID)
            {
                if (entities_.find(entityID) == entities_.end())
                    return;
                // TODO: remove entityID
            }

            void addComponent(EntityId entityId, ComponentId& componentId)
            {
//                entities_[entityId].push_back(componentId);
            }

            void rmComponent(EntityId entityID, ComponentId& ComponentId)
            {
                // TODO: define
            }

            std::vector<std::string> getComponents(EntityId entityID)
            {
//                return entities_[entityID];
            }
        };

    };
};
