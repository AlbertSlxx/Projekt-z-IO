cmake_minimum_required(VERSION 3.24)
project(Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(SOURCE_FILES
        Chambers.cpp
        Chambers.h
        Character.cpp
        Character.h
        Controller.cpp
        Controller.h
        Equipment.cpp
        Equipment.h
        Events.cpp
        Events.h
        Game.cpp
        Game.h
        Items.cpp
        Items.h
        Names.h
        Strategy.cpp
        Strategy.h
        Views.cpp
        Views.h)

include_directories(.)

add_executable(Game ${SOURCE_FILES})