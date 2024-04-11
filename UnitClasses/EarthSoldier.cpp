#include "EarthSoldier.h"
#include "../Containers/LinkedQueue.h"

#include <iostream>

EarthSoldier::EarthSoldier(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::ES, health, power, attackCapacity)
{}

void EarthSoldier::print() const
{
    std::cout << "ES " << this->getId() << " shots [";
    foughtUnits.printList();
    std::cout << "]\n";
}

void EarthSoldier::attack()
{}
