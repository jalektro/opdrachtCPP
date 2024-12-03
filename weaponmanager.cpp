#include "weaponmanager.h"

void WeaponManager::addWeapon(Weapon* weapon) {
    weapons.append(weapon);
}

Weapon* WeaponManager::getWeapon(int index) {
    if (index >= 0 && index < weapons.size()) {
        return weapons[index];
    }
    return nullptr;
}
