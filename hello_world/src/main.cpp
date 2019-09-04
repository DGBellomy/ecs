#include <iostream>
#include <map>

#define MESSAGE_TYPE 0x1

#define UINT unsigned int
#define USHORT unsigned short

// ****************************************************ENTITIES*********************************************************
// MessengerEntity - displays messages


// ****************************************************COMPONENTS*******************************************************

struct MessageComponent {
    UINT entity_id;
    bool active;
    const char* message;
    unsigned short len;
};

// ****************************************************COMPONENT*LIST***************************************************

// holds a compact list of components of a specific type
// contains a hash map to quickly access a component by entity_id
template <typename T>
class ComponentList {
    USHORT _active; // number of active components
    USHORT _size; // size of container
    T* _componentList; // compact list of active components
    std::map<UINT, USHORT> _idMap; // map entity_id to index in compact list for quick lookup

public:
    // get a component by entity_id
    T* get(UINT entity_id)
    {
        USHORT index = _idMap[entity_id];
        return &_componentList[index];
    }

    // get the entire compact component list (for read or write?)
    T* get()
    {
        return _componentList;
    }

    // add a component to the list and to the mapper
    void add(T component)
    {
        if (_active < _size)
        {
            _componentList[_active] = component;
            _idMap[component.entity_id] = _active;
            _active++;
        }
        else
        {
            // resize
        }
    }

    // remove a component from the list and mapper
    void remove(UINT entity_id)
    {
        USHORT index = _idMap[entity_id];
        _componentList[index] = _componentList[_active];
        _idMap.erase(entity_id);
        _active--;
    }

    // disable a compoent in the list and update mapper
    void disable(UINT entity_id)
    {
        USHORT index = _idMap[entity_id];
        T component = _componentList[index];
        component.active = false;
    }

    // enable a component in the list and update mapper
    void enable(UINT entity_id)
    {
        USHORT index = _idMap[entity_id];
        T component = _componentList[index];
        component.active = true;
    }
};

// ****************************************************SYSTEMS**********************************************************
class ISystem {
public:
    virtual void run() = 0;
};

class GetMessageSystem : public ISystem {
    MessageComponent* _messageComponents;

public:
    virtual void run() override
    {
        for (int i = 0; i < 55; ++i)
        {
            char buffer[256];
            sprintf(buffer, "this message is from %d", _messageComponents[i].entity_id);
            _messageComponents[i].message = buffer;
        }
    }
};

class DisplayMessageSystem : public ISystem {
    MessageComponent* _messageComponents;

public:
    virtual void run() override
    {
        for (int i = 0; i < 55; ++i)
        {
            printf("%s", _messageComponents[i].message);
        }
    }
};

// ****************************************************ENGINE***********************************************************
class Engine {
public:
};


// ****************************************************MAIN*************************************************************
int main()
{
    // add components
    // add systems (connect components to the systems)
    // init engine (add systems to the engine)
}
