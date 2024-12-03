cmake_minimum_required(VERSION 3.16)

project(WeaponSystemAPI LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# Zoek Qt6 inclusief Core, WebSockets en Network componenten
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets WebSockets Network Pdf PdfWidgets)

# Stel de executable in en link de Qt6 componenten
add_executable(WeaponSystemAPI main.cpp
    websocketserver.h websocketserver.cpp
    mainwindow.h mainwindow.cpp
    resources.qrc
    explosiveview.h explosiveview.cpp
    part.h part.cpp)
target_link_libraries(WeaponSystemAPI Qt6::Core Qt6::WebSockets Qt6::Network)
target_link_libraries(WeaponSystemAPI Qt6::Gui Qt6::Widgets Qt6::Pdf Qt6::PdfWidgets)
target_link_libraries(WeaponSystemAPI Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS WeaponSystemAPI
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

