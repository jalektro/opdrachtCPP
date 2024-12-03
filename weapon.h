#ifndef WEAPON_H
#define WEAPON_H

#include <QString>

class Weapon
{
public:

    Weapon(const QString &name = "", const QString &imagePath = "", const QString &pdfPath = "", const QString &explodedViewPath = "");

    virtual ~Weapon() = default;

    QString getName() const;
    QString getImagePath() const;
    QString getPdfPath() const;
    QString getExplodedViewPath() const;

    virtual QString getSpecialFeature() const; // Add extra info about the weapon ptherwise return standard weapon. (not needed)

private:
    QString weaponName;
    QString imageWeaponPath;
    QString pdfPath;
    QString explodedViewPath;
};

#endif // WEAPON_H
