QT       += core gui widgets pdf pdfwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    pdfhandler.cpp \
    scarh.cpp \
    scarl.cpp \
    weapon.cpp \
    weaponmanager.cpp

HEADERS += \
    mainwindow.h \
    pdfhandler.h \
    scarh.h \
    scarl.h \
    weapon.h \
    weaponmanager.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/explodedView.qrc \
    resources/images.qrc \
    resources/pdf.qrc


