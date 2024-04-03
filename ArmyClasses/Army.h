#ifndef ARMY_H
#define ARMY_H

class Army
{
public:
    virtual void addUnit() = 0; // Will take a pointer to Unit as a parameter
    virtual void removeUnit() = 0;
    virtual void print() const = 0;
    virtual void attack() = 0;
};

#endif

