cmake_minimum_required(VERSION 3.15)
project(ecs_examples)

set(CMAKE_CXX_STANDARD 98)

include_directories(include)

add_executable(ecs_examples
        include/ecs
        include/coreECS/Common.h
        include/coreECS/ComponentList.h
        include/coreECS/ComponentStore.h
        include/coreECS/EntityStore.h
        include/coreECS/Systems.h
        src/main.cpp)
