#ifndef SCARL_H
#define SCARL_H

#include "weapon.h"

class SCARL : public Weapon
{
public:
    SCARL();
    QString getSpecialFeature() const override; // Override to provide unique behavior
};

#endif // SCARL_H
