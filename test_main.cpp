#include <iostream>
#include "ecs/ECS.h"
#include "Components.h"

void InputSystem() {
    int x, y;
    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "\nEnter y: ";
    std::cin >> y;
    std::cout << std::endl;

    forEachComponent(position, Position, {
        if (x != position->data.x || y != position->data.y) {
            Velocity *velocity = ecs::Components::get<Velocity>(position->entityID);
            velocity->data.x = x - position->data.x;
            velocity->data.y = y - position->data.y;
        }
    })
}

void MoveSystem() {
    forEachComponent(velocity, Velocity, {
        if (velocity->data.x != 0 || velocity->data.y != 0) {
            Position *position = ecs::Components::get<Position>(velocity->entityID);
            position->data.x += velocity->data.x;
            position->data.y += velocity->data.y;
        }
    })
}

void ShowLists() {
    std::puts("VELOCITY:");
    forEachComponent(velocity, Velocity, {
        std::printf("velocity: { x: %d, y: %d, entityID: %d }\n", velocity->data.x, velocity->data.y,
                    velocity->entityID);
    })

    std::puts("\nPOSITION:");
    forEachComponent(position, Position, {
        std::printf("position: { x: %d, y: %d, entityID: %d }\n", position->data.x, position->data.y,
                    position->entityID);
    })

    std::printf("Win32: { x: %d, y: %d }\n", Win32.x, Win32.y);

    ecs::Systems::stop();
}

void createGoblin(int posX, int posY) {
    Position position = {posX, posY};
    Velocity velocity = {0, 0};

    ecs::Entity entity("Goblin");
    entity.addComponent(position);
    entity.addComponent(velocity);
}

int main() {
    createGoblin(5, 7);
    createGoblin(12, 43);

    Win32.x = 9;
    Win32.y = 72;

    ecs::Systems::onInit(InputSystem);
    ecs::Systems::onInit(MoveSystem);
    ecs::Systems::onStart(ShowLists);

    std::puts("Starting ecs Systems");
    ecs::Systems::run();

    return 0;
}
