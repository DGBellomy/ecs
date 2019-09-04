#include <iostream>
#include "Common.h"
#include "Components.h"
#include "ComponentList.h"


void createMessageEntity()
{
    ComponentList<MessageComponent>* messages = ComponentList<MessageComponent>().instance();

    MessageComponent msgComp1;
    msgComp1.entity_id = 1;
    msgComp1.active = true;
    msgComp1.message = "test";
    msgComp1.len = 0;
    messages->add(msgComp1);

    MessageComponent msgComp2;
    msgComp2.entity_id = 2;
    msgComp2.active = true;
    msgComp2.message = "test";
    msgComp2.len = 0;
    messages->add(msgComp2);

    MessageComponent* msgList = messages->get();

    for (USHORT i = 0; i < messages->active(); ++i)
    {
        printf("message %d: %d - %s\n", i, msgList[i].entity_id, msgList[i].message);
    }
}

void createTestEntity()
{
    ComponentList<TestComponent>* tests = ComponentList<TestComponent>::instance();

    TestComponent testComp1;
    testComp1.entity_id = 3;
    testComp1.active = true;
    testComp1.message = "test";
    testComp1.len = 0;
    tests->add(testComp1);

    TestComponent testComp2;
    testComp2.entity_id = 4;
    testComp2.active = true;
    testComp2.message = "test";
    testComp2.len = 0;
    tests->add(testComp2);

    TestComponent* testList = tests->get();

    for (USHORT i = 0; i < tests->active(); ++i)
    {
        printf("test %d: %d - %s\n", i, testList[i].entity_id, testList[i].message);
    }
}

int main()
{
    // create components needed by the systems that make up entities
    // add systems (connect components to the systems)
    // init engine (add systems to the engine)

    createMessageEntity();
    createTestEntity();
    createMessageEntity();

    return 0;
}
