/* Author: GarRaptor
 * Description: Interface to the Entity Component System
 */

#pragma once

#include <map>
#include <vector>

#include "ComponentStore.h"

class ECS {
    int entityID_;
    std::map<int, std::vector<std::string>> entities_;

    ECS():
        entityID_(0),
        entities_()
    {}

    ECS(const ECS&) = delete;
    ECS(const ECS&&) = delete;
    ECS& operator= (const ECS&) = delete;
    ECS& operator= (const ECS&&) = delete;

public:

    static ECS* getInstance()
    {
        static ECS* instance = new ECS();
        return instance;
    }

    int registerEntity();
    void rmEntity(int entityID);

    template <typename T> void addComponent(const T& component);
    template <typename T> void rmComponent(const std::string& name);
    template <typename T> T* getComponent(int entityID, const std::string& name);
    template <typename T> void activateComponent(int entityID, const std::string& name);
    template <typename T> void deactivateComponent(int entityID, const std::string& name);

    // void addSystem(void (funcPtr)(void));
    // void rmSystem(void (funcPtr)(void));
    // void enableSystem(void (funcPtr)(void));
    // void disableSystem(void (funcPtr)(void));

    template <typename T> T* getComponentList(const std::string& name);
    int* getEntityList(const std::string* componentTuple);
    // TODO: get ComponentList with list of entity IDs
};

// PUBLIC MODIFYING FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int ECS::registerEntity()
{
    entities_[entityID_];
    return entityID_++;
}
