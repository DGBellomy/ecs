#include "entity.h"

bool Entity::add(Component *component)
{
    if (component != nullptr)
    {
        // do the stuff to add component
    }
    return false;
}

bool Entity::remove(const char* componentName)
{
    if (strncmp(componentName, "") != 0)
    {
        // do the stuff to remove component
    }
    return false;
}

Component* Entity::get(const char* componentName)
{
    if (componentName != "")
    {
        // do the stuff to get component
    }
    return nullptr;
}
