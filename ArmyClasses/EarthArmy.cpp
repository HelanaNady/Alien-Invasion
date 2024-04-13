#include <iostream>

#include "EarthArmy.h"
#include "../UnitClasses/Unit.h"

void EarthArmy::addUnit(Unit* unit)
{
    UnitType unitType = unit->getUnitType();

    switch (unitType)
    {
        case UnitType::ES:
            soldiers.enqueue(unit);
            break;
       
        case UnitType::ET:
            tanks.push(unit);
            break;

        default:
            gunneries.enqueue(unit, unit->getHealth() + unit->getPower());
            break;
    }
}

Unit* EarthArmy::removeUnit(UnitType unitType)
{
    Unit* unit = nullptr;

    switch (unitType)
    {
        case UnitType::ES:
            soldiers.dequeue(unit);
            break;

        case UnitType::ET:
            tanks.pop(unit);
            break;

        default:
            int dummyPri;
            gunneries.dequeue(unit, dummyPri);
            break;
    }

    return unit;
}

Unit* EarthArmy::pickAttacker(UnitType unitType)
{
    Unit* unit = nullptr;
    int dummyPri = 0; 

    switch (unitType)
    {
        case UnitType::ES:
            soldiers.peek(unit);
            break;
        case UnitType::EG:
            gunneries.peek(unit, dummyPri);
            break;
        case UnitType::ET:
            tanks.peek(unit);
            break;
    }

    return unit;
}

int EarthArmy::getUnitsCount(UnitType unitType) const 
{
    switch (unitType) 
    {
        case UnitType::ES:
            return soldiers.getCount();
            break;
        case UnitType::EG:
            return gunneries.getCount();
            break;
        case UnitType::ET:
            return tanks.getCount();
            break;
    }
}


void EarthArmy::printArmy() const
{
    std::cout << soldiers.getCount() << " ES [";
    soldiers.printList();
    std::cout << "]" << std::endl;

    std::cout << tanks.getCount() << " ET [";
    tanks.printList();
    std::cout << "]" << std::endl;

    std::cout << gunneries.getCount() << " EG [";
    gunneries.printList();
    std::cout << "]" << std::endl;
}

void EarthArmy::attack()
{
    Unit* attacker = pickAttacker(UnitType::ES);
    if (attacker)
    {
        attacker->attack();
        currentFighters.enqueue(attacker);
    }

    attacker = pickAttacker(UnitType::EG);
    if (attacker)
    {
        attacker->attack();
        currentFighters.enqueue(attacker);
    }
    
    attacker = pickAttacker(UnitType::ET);
    if (attacker)
    {
        attacker->attack();
        currentFighters.enqueue(attacker);
    }
}

bool EarthArmy::isDead()
{
    return soldiers.getCount() + tanks.getCount() + gunneries.getCount() == 0;
}

EarthArmy::~EarthArmy()
{
    // Delete all units in the army
    Unit* unit = nullptr;
    int dummyPri = 0;

    while (soldiers.dequeue(unit))
        delete unit;

    while (tanks.pop(unit))
        delete unit;

    while (gunneries.dequeue(unit, dummyPri))
        delete unit;
}