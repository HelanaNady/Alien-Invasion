#include <iostream>

#include "AlienArmy.h"
#include "../UnitClasses/Unit.h"

AlienArmy::AlienArmy(): dronesToggler(false)
{
}

void AlienArmy::addUnit(Unit* unit)
{
    if (unit->getUnitType() == UnitType::AS)
        soldiers.enqueue(unit);

    else if (unit->getUnitType() == UnitType::AM)
        monsters.insert(unit);

    else
    {
        if (dronesToggler)
            drones.enqueue(unit);
        else
            drones.enqueueFront(unit);

        dronesToggler = !dronesToggler; 
    }
}

Unit* AlienArmy::removeUnit(UnitType unitType) 
{
    Unit* unit = nullptr;

    if (unitType == UnitType::AS)
        soldiers.dequeue(unit); 

    else if (unitType == UnitType::AM)
    {
        int maxCount = monsters.getCount();
        if (!monsters.isEmpty())
        {
            int index = rand() % maxCount;
            monsters.remove(index, unit);
        }
    }

    else
    {
        if (dronesToggler) 
            drones.dequeue(unit);
        else
            drones.dequeueBack(unit);

        dronesToggler = !dronesToggler;
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