#include "HealableUnit.h"
#include "../Game.h"

HealableUnit::HealableUnit(Game* gamePtr, UnitType unitType, double health, int power, int attackCapacity)
    : Unit(gamePtr, unitType, health, power, attackCapacity)
{
    UMLjoinTime = 0;
}

bool HealableUnit::needsHeal() const
{
    return (health / initialHealth) <= 0.2;
}

void HealableUnit::receiveHeal(double UHP)
{
    // Infected units get twice the time to get healed
    if (dynamic_cast<EarthSoldier*>(this) && dynamic_cast<EarthSoldier*>(this)->isInfected())
        health += UHP / 2;
    else
        health += UHP;
}

void HealableUnit::setUMLjoinTime(int UMLjoinTime)
{
    this->UMLjoinTime = UMLjoinTime;
}

bool HealableUnit::hasWaitedForTooLong() const
{
    // Check if it has spent more than 10 consecutive timesteps in the UML
    return gamePtr->getCurrentTimestep() - UMLjoinTime > 10;
}

bool HealableUnit::isHealed() const
{
    // A unit is healed if its health is more than 20% of its initial health
    return health > initialHealth * 0.2;
}

bool HealableUnit::wasInfected() 
{
    if (unitType == UnitType::ES)
    {
        return dynamic_cast<EarthSoldier*>(this)->isInfected();
    }
    return false;
}
