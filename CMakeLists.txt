cmake_minimum_required(VERSION 3.26)
project(Alien_Invasion)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Alien_Invasion
        main.cpp
        Containers/ArrayStack.h
        Containers/Deque.h
        Containers/LinkedQueue.h
        Containers/Node.h
        Containers/PriorityNode.h
        Containers/PriorityQueue.h
        Containers/QueueADT.h
        Containers/StackADT.h
        RandomGenerator/RandomGenerator.cpp
        UnitClasses/AlienDrone.cpp
        UnitClasses/AlienMonster.cpp
        UnitClasses/AlienSoldier.cpp
        UnitClasses/EarthGunnery.cpp
        UnitClasses/EarthSoldier.cpp
        UnitClasses/EarthTank.cpp
        UnitClasses/HealUnit.cpp
        UnitClasses/Unit.cpp
        Game.cpp
        ArmyClasses/AlienArmy.cpp
        ArmyClasses/EarthArmy.cpp
        ArmyClasses/Army.cpp
        UnitClasses/HealUnit.cpp
        UnitClasses/HealableUnit.cpp)