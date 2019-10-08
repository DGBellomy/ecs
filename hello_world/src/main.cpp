#include <stdio.h>
#include "Common.h"
#include "Engine.h"

struct MessageComponent
{
    UINT entityID;
    USHORT length;
    const char* message;
};

struct DisplayComponent
{
    UINT entityID;
    USHORT length;
    const char* message;
};

struct DisplayList
{
    USHORT active;
    DisplayComponent* list;
    std::map<UINT, USHORT> map;
};

struct MessageList
{
    USHORT active;
    MessageComponent* list;
    std::map<UINT, USHORT> map;
};

//*********************************************************************************************************************

MessageComponent& getComponent(MessageList& messages, UINT entityID)
{
    USHORT index = messages.map[entityID];
    return messages.list[index];
}

DisplayComponent& getComponent(DisplayList& displays, UINT entityID)
{
    USHORT index = displays.map[entityID];
    return displays.list[index];
}

//*********************************************************************************************************************

void notifySystem(MessageList& messages, DisplayList& displays)
{
    for (USHORT i = 0; i < messages.active; ++i)
    {
        MessageComponent message = messages.list[i];
        getComponent(displays, message.entityID).message = message.message;
    }
}

void displaySystem(DisplayList& displays)
{
    for (USHORT i = 0; i < displays.active; ++i)
    {
        printf("%s", displays.list[i].message);
    }
}

//*********************************************************************************************************************

int main()
{
    // create components needed by the systems that make up entities
    // add systems (connect components to the systems)
    // init engine (add systems to the engine)

    // create message component
    // create display component

    // create notify system
    // create display system

    // while true:
    //   notify_system (messages, displays)
    //   display_system (messages, displays)

    return 0;
}
