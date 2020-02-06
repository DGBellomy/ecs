# ecs_examples
Creating sample ECS projects to learn how ECS works for data-oriented projects.

# interface
```
ECS* ecs = ECS::instance();
int entity_id = ecs->registerEntity();

ecs->addComponent<T>(entity_id, component);
ecs->rmComponent<T>(entity_id, componentName);
ecs->getComponent<T>(entity_id, componentName);
ecs->activateComponent<T>(entity_id, componentName);
ecs->deactivateComponent<T>(entity_id, componentName);

ecs->addSystem(systemFunc);
ecs->rmSystem(systemName);
ecs->enableSystem(systemName);
ecs->disableSystem(systemName);

ecs->getComponentList<T>(componentName);
ecs->getEntityListByTuples(componentNames);
```


# interface to setup entity
```
int entity_id = ECS::registerEntity();
Comp newComp = Comp();
ECS::addComponent<Comp>(entity_id, newComp);
...
// DONE
```

# interface to setup system
```
void MoveSystem()
{
    Comp* componentList = ECS::getComponentList(Comp::ID());

    for (int i = 0; i < ECS::size(Comp::ID()); i++)
    {
        // do stuff
    }
}
```
