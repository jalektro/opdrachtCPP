#ifndef WEAPONMANAGER_H
#define WEAPONMANAGER_H

#include <QObject>
#include <QVector>
#include "weapon.h"

class WeaponManager : public QObject {
    Q_OBJECT
public:
    QVector<Weapon*> weapons;

    void addWeapon(Weapon* weapon);

    Weapon* getWeapon(int index);

};

#endif // WEAPONMANAGER_H
