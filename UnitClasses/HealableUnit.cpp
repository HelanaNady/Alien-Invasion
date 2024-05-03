#include "HealableUnit.h"

HealableUnit::HealableUnit(Game* gamePtr, UnitType unitType, double health, int power, int attackCapacity)
    : Unit(gamePtr, unitType, health, power, attackCapacity)
{}

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