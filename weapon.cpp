#include "weapon.h"

Weapon::Weapon(const QString &name, const QString &imagePath,
               const QString &pdfPath, const QString &explodedViewPath)
    : weaponName(name), imageWeaponPath(imagePath),
    pdfPath(pdfPath), explodedViewPath(explodedViewPath) {}

QString Weapon::getName() const { return weaponName; }
QString Weapon::getImagePath() const { return imageWeaponPath; }
QString Weapon::getPdfPath() const { return pdfPath; }
QString Weapon::getExplodedViewPath() const { return explodedViewPath; }


QString Weapon::getSpecialFeature() const
{
    return "Standard Weapon";
}
