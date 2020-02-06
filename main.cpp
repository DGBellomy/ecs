#include "ecs/ECS.h"

Component(Position,
    int x;
    int y;
);

// create a system that handles a "COMPONENT"

void myCallback()
{
    // CompList components = ecs::getComponentList<CompType>();

    // TODO: assuming an entity holds ptrs to it's components???
    // for (component in components) {
    //   if (component.property > 5) {
    //     CompType* component = ecs::getComponentRef<CompType>(component1.entityId);
    //     component->someProperty = value;
    //   }
    // }
}

int main()
{
    // create components to be assigned to an entity
    // create new entity and assign the components

    // Position ps = { 5, 7 };
    // Velocity v = { 0, 0 };

    // createEntity([...]) with list of components

    // TODO: figure out what the hell I'm going to do
    // TODO: make typedef (entityID => unsigned int)

    // entityID entityId = ecs::getNewEntityId();
    // ecs::addComponent<CompType1>(entityId, component1);
    // ecs::addComponent<CompType2>(entityId, component2);
    // ecs::registerEntity(entityId);

    // TODO: callback will be a function ptr
    // TODO: priority will default to 5 - [0:9]???
    // ecs::registerSystem(callback, priority);

    return 0;
}
