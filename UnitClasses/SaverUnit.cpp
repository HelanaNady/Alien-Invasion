#include "SaverUnit.h"
#include "../Game.h"

SaverUnit::SaverUnit(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AM, health, power, attackCapacity)
{}

void SaverUnit::printFought()
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "SU " << getId() << " shots [";
        foughtUnits.printList();
        std::cout << "]" << std::endl;

        clearFoughtUnits(); // Clear the list after printing
    }
}

bool SaverUnit::attack()
{
    // implemented just like ES attack 
    return false;
}
