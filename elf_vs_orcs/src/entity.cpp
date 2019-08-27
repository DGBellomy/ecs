#include "entity.h"

bool Entity::add(Component component)
{
    EntityMap::iterator it = componentDict.find(component.getKey());
    if (it == componentDict.end())
    {
        componentDict.insert(EntityPair(component.getKey(), component));
        return true;
    }
    return false;
}

bool Entity::remove(unsigned int componentKey)
{
    EntityMap::iterator it = componentDict.find(componentKey);
    if (it != componentDict.end())
    {
        componentDict.erase(it);
    }
    return false;
}

Component* Entity::get(unsigned int componentKey)
{
    EntityMap::iterator it = componentDict.find(componentKey);
    if (it != componentDict.end())
    {
        return &it->second;
    }
    return nullptr;
}
