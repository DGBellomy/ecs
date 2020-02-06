#include <iostream>
#include "ecs/ECS.h"

Component(Position,
          int x;
                  int y;
);

Component(Velocity,
          int x;
                  int y;
);

// create a system that handles a "COMPONENT"

void InputSystem() {
    // TODO: make typedef (CompId => std::string)
    // TODO: make typedef (CompList => vector<CompId, void*>)
    // CompType* components = ecs::getComponentList<CompType>();

    int x, y;
    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "\nEnter y: ";
    std::cin >> y;
    std::cout << std::endl;

    Position *positionList = ecs::getComponentList<Position>();

    for (int i = 0; i < ecs::length(Position::ID()); i++) {
        // TODO: do the stuff
    }

    // TODO: assuming an entity holds ptrs to it's components???
    // for (component in components) {
    //   if (component.property > 5) {
    //     CompType* component = ecs::getComponent<CompType>(component1.entityId, T::ID());
    //     component->someProperty = value;
    //   }
    // }
}

void MoveSystem() {
    // TODO: make move system
}

int main() {
    // TODO: create components to be assigned to an entity
    // or.................................
    // TODO: create new entity and assign the components

    Position position = {5, 7};
    Velocity velocity = {0, 0};

    std::printf("%s: { x: %d, y: %d, id: %d }\n", Position::ID().c_str(), position.x, position.y, position.entityID);
    std::printf("%s: { x: %d, y: %d, id: %d }\n", Velocity::ID().c_str(), velocity.x, velocity.y, velocity.entityID);

    // ecs::createEntity([...]) with list of components

    // TODO: figure out what the hell I'm going to do
    // TODO: make typedef (entityID => unsigned int)

    EntityId entityId = ecs::getNewEntityId();
    ecs::addComponent<Position>(entityId, position);
    ecs::addComponent<Velocity>(entityId, velocity);
    // ecs::registerEntity(entityId); (No use???)

    // TODO: callback will be a function ptr
    // TODO: priority will default to 5 - [0:9]???
    ecs::registerSystem(InputSystem);
    ecs::registerSystem(MoveSystem);

    ecs::run();

    return 0;
}
