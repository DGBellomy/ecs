#include <stdio.h>
#include <string>

#include "utils.h"
#include "component_list.h"
#include "ComponentStore.h"

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


void compare_func_ptrs()
{
    void* pv = 0;
    void (*pfn)() = 0;
    int STest::*pmv = 0;
    void (STest::*pmf)(int) const = 0;

    printf("pv: %lu\n", sizeof(pv));
    printf("pfn: %lu\n", sizeof(pfn));
    printf("pmv: %lu\n", sizeof(pmv));
    printf("pmf: %lu\n", sizeof(pmf));
}

void check_tolower()
{
    std::string name = "HERALD\n";
    printf("name: %s", dgb::utils::tolower(name).c_str());
    printf("name: %s", dgb::utils::tolower("HELLO\n").c_str());
}

// COMPONENTS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

struct Component {
    static const std::string name;
    int entityID;
};

struct PositionComponent : public Component {
    int x;
    int y;
};

struct VelocityComponent {
    static const std::string name;
    int entityID;
    int x;
    int y;
    bool isMoving;
};
const std::string VelocityComponent::name = "velocity";

// COMPONENTS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void check_component_list()
{
    PositionComponent pc;
    pc.entityID = 0;
    pc.x = 3;
    pc.y = 7;

    component_list comp;
    comp.append<PositionComponent>(pc);
    PositionComponent* componentList = comp.get<PositionComponent>();

    for (int i = 0; i < comp.size(); i++)
    {
        printf("pc: {%d, %d, %d}\n", componentList[i].entityID, componentList[i].x, componentList[i].y);
    }
}

void check_component_store()
{
    ComponentStore* cs = ComponentStore::getInstance();

    cs->addComponentList(PositionComponent::name);
    PositionComponent pc;
    pc.entityID = 0;
    pc.x = 3;
    pc.y = 7;
    cs->addComponent<PositionComponent>(pc);
    pc.entityID = 1;
    pc.x = 9;
    pc.y = 33;
    cs->addComponent<PositionComponent>(pc);

    cs->addComponentList(VelocityComponent::name);
    VelocityComponent vc;
    vc.entityID = 0;
    vc.x = 8;
    vc.y = 1;
    vc.isMoving = false;
    cs->addComponent<VelocityComponent>(vc);
    vc.entityID = 1;
    vc.x = 6;
    vc.y = 2;
    vc.isMoving = true;
    cs->addComponent<VelocityComponent>(vc);

    PositionComponent* ppc = cs->getComponentList<PositionComponent>(PositionComponent::name);
    for (int i = 0; i < 2; i++)
    {
        printf("position: {%d, %d, %d}\n", ppc[i].entityID, ppc[i].x, ppc[i].y);
        printf("position loc: %ld\n", reinterpret_cast<long>(&ppc[i]));
    }

    VelocityComponent* pvc = cs->getComponentList<VelocityComponent>(VelocityComponent::name);
    for (int i = 0; i < 2; i++)
    {
        printf("velocity: {%d, %d, %d, %d}\n", pvc[i].entityID, pvc[i].x, pvc[i].y, pvc[i].isMoving);
        printf("velocity loc: %ld\n", reinterpret_cast<long>(&pvc[i]));
    }
}

int main()
{
    // compare_func_ptrs();
    // check_tolower();
    // check_component_list();
    check_component_store();

    return 0;
}

