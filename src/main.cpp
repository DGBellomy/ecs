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

    std::puts("VELOCITY:");
    for (int i = 0; i < activeVelocityComponents; i++) {
        std::printf("velocity: { x: %d, y: %d, entityID: %d }\n", velocityList[i].x, velocityList[i].y, velocityList[i].entityID);
    }

    Position *positionList = ecs::getComponentList<Position>();
    const int activePositionComponents = ecs::numActive(Position::ID());

    std::puts("\nPOSITION:");
    for (int i = 0; i < activePositionComponents; i++) {
        std::printf("position: { x: %d, y: %d, entityID: %d }\n", positionList[i].x, positionList[i].y, positionList[i].entityID);
    }

    ecs::stop();
}

void createGoblin(int posX, int posY) {
    Position position = {posX, posY};
    Velocity velocity = {0, 0};

    EntityId entityId = ecs::getNewEntityId();
    ecs::addComponent(entityId, position);
    ecs::addComponent(entityId, velocity);
}

int main() {
    createGoblin(5, 7);
    createGoblin(12, 43);

    ecs::registerSystem(InputSystem, OnInit);
    ecs::registerSystem(MoveSystem, OnInit);
    ecs::registerSystem(ShowLists, OnStart);

    std::puts("Starting ECS Systems");
    ecs::run();

    return 0;
}
