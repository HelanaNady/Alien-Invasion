#include <iostream>

#include "AlienArmy.h"
#include "../UnitClasses/Unit.h"

AlienArmy::AlienArmy(): dronesToggler(false)
{
}

void AlienArmy::addUnit(Unit* unit)
{
    if (unit->getUnitType() == UnitType::AS)
        soldiers.enqueue(dynamic_cast<AlienSoldier*>(unit));
    else if (unit->getUnitType() == UnitType::AM)
        monsters.insert(dynamic_cast<AlienMonster*>(unit));
    else
    {
        if (dronesToggler)
            drones.enqueue(dynamic_cast<AlienDrone*>(unit));
        else
            drones.enqueueFront(dynamic_cast<AlienDrone*>(unit));

        dronesToggler = !dronesToggler; 
    }
}

Unit* AlienArmy::removeUnit(UnitType unitType) 
{
    Unit* unit = nullptr;

    if (unitType == UnitType::AS)
    {
        AlienSoldier* temp = nullptr; 
        soldiers.dequeue(temp); 
        unit = temp; 
    }
    else if (unitType == UnitType::AM)
    {
        AlienMonster* temp = nullptr;
        int maxCount = monsters.getCount();
        if (!monsters.isEmpty())
        {
            int index = rand() % maxCount;
            monsters.remove(index, temp);
        }
    }
    else
    {
        AlienDrone* temp = nullptr;

        if (dronesToggler) 
            drones.dequeue(temp);
        else
            drones.dequeueBack(temp);

        dronesToggler = !dronesToggler;
        unit = temp;
    }

    return unit;
}

void AlienArmy::print() const
{
    std::cout << "============== Alien Army Alive Units ==============" << std::endl;

    std::cout << soldiers.getCount() << " AS [";
    soldiers.printList();
    std::cout << "]" << std::endl;

    std::cout << monsters.getCount() << " AM [";
    monsters.printList();
    std::cout << "]" << std::endl;
    
    std::cout << drones.getCount() << " AD [";
    drones.printList();
    std::cout << "]" << std::endl;
}

void AlienArmy::attack()
{
}