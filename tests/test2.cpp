#include <stdio.h>
#include <map>


enum ComponentType {
    NUM,
    STR
};

class Entity {
    int m_id;

public:
    static int Count;
    //void addComponent(Component& component)
    //{
    //}
};

int Entity::Count = 0;


class System {
public:
    virtual void update() = 0;
    static void tick()
    {
    }
};


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
