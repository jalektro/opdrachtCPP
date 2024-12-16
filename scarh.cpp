#include "scarh.h"

SCARH::SCARH()
     : Weapon("SCAR-H", ":/images/SCAR-L.jpg", ":/pdf/scar_l.pdf", ":/explodedview/explodedview_scar_l.png") {}


QString SCARH::getSpecialFeature() const {
    return "Standard weapon of choice cal 7.62 nato standard.";
}

