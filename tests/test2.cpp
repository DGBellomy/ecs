#include <stdio.h>
#include <map>


enum ComponentType {
    NUM,
    STR
};

class Entity {
    int m_id;
    static int Count;

public:
    template <class T>
    void addComponent(T& component)
    {
        // add component to store
    }
};

int Entity::Count = 0;


class System {
public:
    virtual void update() = 0;
    static void tick()
    {
    }
};


int createElf()
{
    elf = Entity();
    elf.addComponent<PositionComponent>(PositionComponent(0,0,0))
    elf.addComponent<VelocityComponent>(VelocityComponent(0,0,0))

    return elf.id;
}


int main()
{
    // setup world
    // add entities
    // add systems
    // for (;;)
    // {
    //     for sys in systems:
    //         sys::tick(gameTime);
    // }

    return 0;
}

// flexability in adding:
//      systems
//      components
//      entities to the world
