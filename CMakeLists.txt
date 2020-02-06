cmake_minimum_required(VERSION 3.15)
project(ecs_examples)

set(CMAKE_CXX_STANDARD 98)

include_directories(ecs)
#include_directories(hello_world/include)

add_executable(ecs_examples
        ecs/Common.h
        ecs/ComponentList.h
        ecs/ComponentStore.h
        ecs/ECS.h
        ecs/EntityStore.h
        ecs/Systems.h
#        hello_world/include/Common.h
#        hello_world/include/ComponentList.h
#        hello_world/include/Components.h
#        hello_world/include/DisplayMessageSystem.h
#        hello_world/include/Engine.h
#        hello_world/include/GetMessageSystem.h
#        hello_world/include/ISystem.h
#        hello_world/src/main.cpp
#        test/dumb_shit.cpp
        main.cpp)
