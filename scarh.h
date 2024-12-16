#ifndef SCARH_H
#define SCARH_H

#include "weapon.h"

class SCARH : public Weapon
{
public:
    SCARH();
    QString getSpecialFeature() const override;
};

#endif // SCARH_H

