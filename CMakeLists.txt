cmake_minimum_required(VERSION 3.15)
project(ecs_examples)

set(CMAKE_CXX_STANDARD 98)

add_executable(ecs_examples
        ecs/ECS.h
        ecs/Common.h
        ecs/ComponentList.h
        ecs/ComponentStore.h
        ecs/EntityStore.h
        ecs/Systems.h
        test_main.cpp)
