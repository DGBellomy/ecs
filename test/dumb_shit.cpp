#include <stdio.h>
#include <string>

#include "../ecs/ComponentList.h"
#include "../ecs/ComponentStore.h"

#define PI 3.1415

class Test {
    const int c_MyInt = 45;
    enum {LookAtThisMa=13};

public:
    const int& getInt()
    {
        return c_MyInt;
    }

    virtual void getMa() = 0;
};

class STest : public Test {
    virtual void getMa()
    {
        printf("Hello World!");
    }
};

class ZTest {
    void whaaa()
    {
        printf("Hello World!");
    }
};


void compare_func_ptrs()
{
    void* pv = 0;
    void (*pfn)() = 0;
    int STest::*pmv = 0;
    void (ZTest::*pmf)(void) = 0;
    void (STest::*pmvf)(void) = 0;

    printf("void ptr: %lu\n", sizeof(pv));                       // 8
    printf("function ptr: %lu\n", sizeof(pfn));                  // 8
    printf("member var ptr: %lu\n", sizeof(pmv));                // 8
    printf("member function ptr: %lu\n", sizeof(pmf));           // 16
    printf("member virtual function ptr: %lu\n", sizeof(pmvf));  // 16
}

// COMPONENTS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Component(Position,
    int x;
    int y;
)

Component(Velocity,
    int x;
    int y;
    bool isMoving;
)

// COMPONENTS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void check_component_list()
{
    Position pc;
    pc.entityID = 0;
    pc.x = 3;
    pc.y = 7;

    component_list comp;
    comp.append<Position>(pc);
    Position* componentList = comp.get<Position>();

    for (int i = 0; i < comp.size(); i++)
    {
        printf("pc: {%d, %d, %d}\n", componentList[i].entityID, componentList[i].x, componentList[i].y);
    }
}

int g_ENTITY_ID = 0;
#define Entity()
    // initialize entity

void check_component_store()
{
    ComponentStore* cs = ComponentStore::getInstance();

    if (cs->addComponentList(Position::name))
    {
        Position pc;
        pc.entityID = 0;
        pc.x = 3;
        pc.y = 7;
        cs->addComponent<Position>(pc);
        pc.entityID = 1;
        pc.x = 9;
        pc.y = 33;
        cs->addComponent<Position>(pc);
    }

    if (cs->addComponentList(Velocity::name))
    {
        Velocity vc;
        vc.entityID = 0;
        vc.x = 8;
        vc.y = 1;
        vc.isMoving = false;
        cs->addComponent<Velocity>(vc);
        vc.entityID = 1;
        vc.x = 6;
        vc.y = 2;
        vc.isMoving = true;
        cs->addComponent<Velocity>(vc);
    }

    Position* ppc = cs->getComponentList<Position>(Position::name);
    if (ppc != nullptr)
        for (int i = 0; i < 2; i++)
        {
            printf("position: {%d, %d, %d}\n", ppc[i].entityID, ppc[i].x, ppc[i].y);
            printf("position loc: %ld\n", reinterpret_cast<long>(&ppc[i]));
        }

    Velocity* pvc = cs->getComponentList<Velocity>(Velocity::name);
    if (pvc != nullptr)
        for (int i = 0; i < 2; i++)
        {
            printf("velocity: {%d, %d, %d, %d}\n", pvc[i].entityID, pvc[i].x, pvc[i].y, pvc[i].isMoving);
            printf("velocity loc: %ld\n", reinterpret_cast<long>(&pvc[i]));
        }
}

void testSystem()
{
    printf("Hello...\n");
}

enum SystemExceptions {NOT_IMPLEMENTED};

class System {
public:
    static void Initialize() {throw NOT_IMPLEMENTED;}
    static void PreTick() {throw NOT_IMPLEMENTED;}
    static void Tick() {throw NOT_IMPLEMENTED;}
    static void LateTick() {throw NOT_IMPLEMENTED;}
    static void PostTick() {throw NOT_IMPLEMENTED;}
    static void CleanUp() {throw NOT_IMPLEMENTED;}
};

class MoveSystem : public System {
};

void check_systems()
{
    printf("%lu\n", sizeof(System));
    printf("%lu\n", sizeof(MoveSystem));

    MoveSystem::Initialize();
}

int main()
{
    // compare_func_ptrs();
    // check_tolower();
    // check_component_list();
    // check_component_store();
    check_systems();

    return 0;
}

