/* Author: GarRaptor
 * Description: Keep track of Entities
 *   stores a list of component names associated with an entity.
 */

#pragma once

#include "Common.h"

typedef std::map<ComponentId, void *> ComponentPtrMap;
typedef std::map<EntityId, ComponentPtrMap> EntityMap;
typedef std::map<const std::string, std::vector<EntityId> > TagMap;

namespace ecs {
    namespace entity {

        class EntityStore {
            EntityMap entityMap_;
            TagMap tagMap_;

        public:
            static EntityStore *getInstance() {
                static EntityStore *instance = new EntityStore();
                return instance;
            }

            void addEntity(const EntityId &entityID, const std::string &tag) {
                if (entityMap_.find(entityID) == entityMap_.end()) {
                    entityMap_[entityID];
                    if (!tag.empty()) {
                        if (tagMap_.find(tag) == tagMap_.end())
                            tagMap_[tag];
                        tagMap_[tag].push_back(entityID);
                    }
                }
            }

            void rmEntity(const EntityId &entityID) {
                if (entityMap_.find(entityID) != entityMap_.end()) {
                    entityMap_[entityID].clear();
                    entityMap_.erase(entityID);
                }
            }

            void addComponent(const EntityId &entityId, const ComponentId &componentId, void *const componentPtr) {
                if (entityMap_.find(entityId) != entityMap_.end())
                    entityMap_[entityId][componentId] = componentPtr;
            }

            void *getComponent(const EntityId &entityId, const ComponentId &componentId) {
                if (entityMap_.find(entityId) != entityMap_.end())
                    return entityMap_[entityId][componentId];
                return nullptr;
            }

//            void rmComponent(EntityId entityID, ComponentId& ComponentId)
//            {
//            }

//            std::vector<std::string> getComponents(EntityId entityID)
//            {
//                return entityMap_[entityID];
//            }
        };

    };
};
