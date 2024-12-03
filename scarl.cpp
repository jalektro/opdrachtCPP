#include "scarl.h"

SCARL::SCARL()
    : Weapon("SCAR-L", ":/images/SCAR-L.jpg", ":/pdfs/scar_l.pdf", ":/explodedview/explodedview_scar_l.png") {}

QString SCARL::getSpecialFeature() const {
    return "Standard weapon of choice cal 5.56 nato standard.";
}
