#include <iostream>

#include "EarthArmy.h"
#include "../UnitClasses/Unit.h"
#include "../Game.h"

EarthArmy::EarthArmy(Game* gamePtr): Army(gamePtr)
{}

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

        case UnitType::EG:
            gunneries.enqueue(unit, unit->getHealth() + unit->getPower());
            break;

        case UnitType::EH:
            healers.push(unit);
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

        case UnitType::EG:
            int dummyPri;
            gunneries.dequeue(unit, dummyPri);
            break;

        case UnitType::EH:
            healers.pop(unit);
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

        case UnitType::EH:
            healers.peek(unit);
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

        case UnitType::EH:
            return healers.getCount();
            break;
    }

    return 0;
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

    std::cout << healers.getCount() << " EH [";
    healers.printList();
    std::cout << "]" << std::endl;
}

bool EarthArmy::attack()
{
    bool didArmyAttack = false; // Flag to check if the army attacked

    UnitType unitTypes[4] = { ES, EG, ET, EH };
    for (int i = 0; i < 4; i++)
    {
        Unit* attacker = pickAttacker(unitTypes[i]);

        if (attacker)
        {
            currentAttackers.enqueue(attacker);

            bool didUnitAttack = attacker->attack(); // Attack the enemy
            didArmyAttack = didArmyAttack || didUnitAttack; // If any unit attacked, the army attacked
        }
    }

    return didArmyAttack; // Return whether the army attacked
}

bool EarthArmy::isDead() const
{
    return soldiers.getCount() + tanks.getCount() + gunneries.getCount() == 0;
}

EarthArmy::~EarthArmy()
{
    // Delete all units in the army
    Unit* unit = nullptr;
    int dummyPri = 0;

    while (soldiers.dequeue(unit))
    {
        delete unit;
        unit = nullptr;
    }

    while (tanks.pop(unit))
    {
        delete unit;
        unit = nullptr;
    }

    while (gunneries.dequeue(unit, dummyPri))
    {
        delete unit;
        unit = nullptr;
    }
}