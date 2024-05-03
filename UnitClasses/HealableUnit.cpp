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
    health += UHP;
}

int HealableUnit::getUMLjoinTime() const
{
    return UMLjoinTime;
}

void HealableUnit::setUMLjoinTime(int UMLjoinTime)
{
    this->UMLjoinTime = UMLjoinTime;
}

bool HealableUnit::hasWaitedForTooLong() const
{
    // Check if it has spent more than 10 consecutive timesteps in the UML
    return gamePtr->getCurrentTimestep() - this->getUMLjoinTime() > 10;
}

bool HealableUnit::isHealed() const
{
    // A unit is healed if its health is more than 20% of its initial health
    return this->getHealth() > this->getInitialHealth() * 0.2;
}
