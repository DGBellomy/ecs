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
    int x, y;
    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "\nEnter y: ";
    std::cin >> y;
    std::cout << std::endl;

    Position *positionList = ecs::getComponentList<Position>();
    const int activePositionComponents = ecs::numActive(Position::ID());

    for (int i = 0; i < activePositionComponents; i++) {
        // TODO: do the stuff
        Position position = positionList[i];
        if (x != position.x || y != position.y) {
            Velocity* velocity = ecs::getComponent<Velocity>(position.entityID);
            velocity->x = x - position.x;
            velocity->y = y - position.y;
        }
    }
}

void MoveSystem() {
    Velocity *velocityList = ecs::getComponentList<Velocity>();
    const int activeVelocityComponents = ecs::numActive(Velocity::ID());

    for (int i = 0; i < activeVelocityComponents; i++) {
        if (velocityList[i].x != 0 || velocityList[i].y != 0) {
            Position *position = ecs::getComponent<Position>(velocityList[i].entityID);
            position->x += velocityList[i].x;
            position->y += velocityList[i].y;
        }
    }
}

void ShowLists() {
    Velocity *velocityList = ecs::getComponentList<Velocity>();
    const int activeVelocityComponents = ecs::numActive(Velocity::ID());

    std::puts("VELOCITY: \n");
    for (int i = 0; i < activeVelocityComponents; i++) {
        std::printf("velocity: { x: %d, y: %d, entityID: %d }\n", velocityList[i].x, velocityList[i].y, velocityList[i].entityID);
    }

    Position *positionList = ecs::getComponentList<Position>();
    const int activePositionComponents = ecs::numActive(Position::ID());

    std::puts("POSITION: \n");
    for (int i = 0; i < activePositionComponents; i++) {
        std::printf("position: { x: %d, y: %d, entityID: %d }\n", positionList[i].x, positionList[i].y, positionList[i].entityID);
    }
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
    ecs::registerSystem(ShowLists);

    ecs::run();

    return 0;
}
