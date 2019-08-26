#include <stdio.h>
#include <string.h>
#include "entity.h"

bool Entity::add(Component component)
{
    if (componentDict.find(component.getName()) == componentDict.end())
    {
        componentDict[component.getName()] = component;
        return true;
    }
    return false;
}

bool Entity::remove(const char* componentName)
{
    if (componentDict.find(componentName) != componentDict.end())
    {
        componentDict.erase(componentName);
    }
    return false;
}

Component* Entity::get(const char* componentName)
{
    if (componentDict.find(componentName) != componentDict.end())
    {
        return &componentDict[componentName];
    }
    return nullptr;
}
