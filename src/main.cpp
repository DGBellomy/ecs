#include <iostream>
#include <ecs>

Component(Position, {
    int x;
    int y;
})

Component(Velocity, {
    int x;
    int y;
})

// create a system that handles a "COMPONENT"

// Traverse over each active component in
#define forEachComponent(component, ComponentType) \
    ComponentType * list_##component = ecs::getComponentList<ComponentType>();\
    const int active_##component = ecs::numActive(ComponentType::ID());\
    ComponentType& component = list_##component[0];\
    for (int i = 0; i < active_##component; component = list_##component[++i])

void InputSystem() {
    int x, y;
    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "\nEnter y: ";
    std::cin >> y;
    std::cout << std::endl;

    forEachComponent(position, Position) {
        if (x != position.data.x || y != position.data.y) {
            Velocity *velocity = ecs::getComponent<Velocity>(position.entityID);
            velocity->data.x = x - position.data.x;
            velocity->data.y = y - position.data.y;
        }
    }
}

void MoveSystem() {
    forEachComponent(velocity, Velocity) {
        if (velocity.data.x != 0 || velocity.data.y != 0) {
            Position *position = ecs::getComponent<Position>(velocity.entityID);
            position->data.x += velocity.data.x;
            position->data.y += velocity.data.y;
        }
    }
}

void ShowLists() {
    std::puts("VELOCITY:");
    forEachComponent(velocity, Velocity) {
        std::printf("velocity: { x: %d, y: %d, entityID: %d }\n", velocity.data.x, velocity.data.y,
                    velocity.entityID);
    }

    std::puts("\nPOSITION:");
    forEachComponent(position, Position) {
        std::printf("position: { x: %d, y: %d, entityID: %d }\n", position.data.x, position.data.y,
                    position.entityID);
    }

    Position *positionList = ecs::getComponentList<Position>();
    const int activePositionComponents = ecs::numActive(Position::ID());

    for (int i = 0; i < activePositionComponents; i++) {
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

    std::puts("Starting coreECS Systems");
    ecs::run();

    return 0;
}
