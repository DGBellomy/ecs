#include <stdio.h>
#include <map>
#include <string>

enum ComponentTypes {};

class Component {
    int m_entityID;
    ComponentTypes m_type;
    void* m_data;

public:
    template<typename T>
    void addComponent(T* component) {

    }
};

class EntityContainer {
    // play with my privates
    static int m_entityIDs;
    std::map<std::string, int> m_entities;
    std::map<ComponentTypes, Component> m_components;

    
public:
    // expose my privates!!!
    static EntityContainer* Instance() {
        static EntityContainer* instance = new EntityContainer();
        return instance;
    }

    void createEntity(std::string name) {
        m_entities[name] = m_entityIDs;
        m_entityIDs++;
    }

    template<typename T>
    void addComponent(T* component) {
    }
};
int EntityContainer::m_entityIDs = 0;




const int POSITION_COMPONENT = 1;

struct PosComp {
    int entityID;
    int x, y;
};

struct ComponentList {
    int id;
    int active;
    std::map<int, int> indexMap;
    void* components;
};


template <typename T>
void addComponent(int compListID, void* component, std::map<int, ComponentList>& _ComponentLists)
{
    ComponentList& compList =  _ComponentLists[compListID];
    if (!compList.components)
    {
        T* tempComponents = new T[64];
        compList.components = reinterpret_cast<void*>(tempComponents);
    }

    // cast from void* to a T* array
    T* tComponents = reinterpret_cast<T*>(compList.components);
    // cast from a void* to a T*, that points to the component to add
    T* tComponentPtr = reinterpret_cast<T*>(component);

    // add component to array
    tComponents[compList.active] = *tComponentPtr;
    compList.indexMap[tComponentPtr->entityID] = compList.active;
    compList.active++;
}

void testAddComponent()
{
    std::map<int, ComponentList> compLists;
    ComponentList posCompList = {1, 0};
    compLists[POSITION_COMPONENT] = posCompList;

    int entityID = 11;
    PosComp posComp = {entityID, 5, 5};
    addComponent<PosComp>(POSITION_COMPONENT, &posComp, compLists);

    ComponentList retrievePosComp = compLists[POSITION_COMPONENT];
    int index = retrievePosComp.indexMap[entityID];
    PosComp* comps = reinterpret_cast<PosComp*>(retrievePosComp.components);
    PosComp actualPosComp = comps[index];
    printf("<%d,%d> is <x=5,y=5>", actualPosComp.x, actualPosComp.y);

}

int main()
{
    testAddComponent();

    return 0;
}
