/* Author: GarRaptor
 * Description: Keep track of Entities
 */

#pragma once

#include <map>
#include <vector>
#include <string>

class Entity {
    static int ID_ = 0;
    std::map<int, std::vector<std::string>> entities_;

public:
    static Entity* getInstance()
    {
        static Entity* instance = new Entity();
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
