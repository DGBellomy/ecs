#include <stdio.h>
#include <string>

#include "utils.h"
#include "component_vector.h"
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

void check_component_vector()
{
    component_vector comp;
    comp.push<int>(9);
    comp.push<int>(3);
    comp.push<int>(5);
    int* list = comp.get<int>();

    for (int i = 0; i < comp.size(); i++)
    {
        printf("int: %d\n", list[i]);
    }
}

struct PositionComponent {
    static const std::string name;
    int entityID;
    int x;
    int y;
};
const std::string name = "position";

void check_component_store()
{
    ComponentStore* cs = ComponentStore::getInstance();
    PositionComponent pc;
    pc.entityID = 0;
    pc.x = 3;
    pc.y = 7;
    cs->addComponent<PositionComponent>(pc);
    pc.entityID = 1;
    pc.x = 9;
    pc.y = 33;
    cs->addComponent<PositionComponent>(pc);

    // print component names
    // print values
    PositionComponent* ppc = cs->getComponents<PositionComponent>(PositionComponent::name);
    for (int i = 0; i < 2; i++)
    {
        printf("position: {%d, %d, %d}", ppc[i].entityID, ppc[i].x, ppc[i].y);
    }
}

int main()
{
    check_component_store();

    return 0;
}

