#include <QMessageBox>
#include <QLabel>
#include "mainwindow.h"
#include "scarl.h"
#include <QPdfSearchModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    centralWidget(new QWidget( this )),
    gridLayout( new QGridLayout)
{
    setCentralWidget(centralWidget);
    centralWidget->setLayout(gridLayout);

    setupWeapons();
    populateWeaponButtons();
}

MainWindow::~MainWindow() {
    // Clean up dynamically allocated weapons
    qDeleteAll(weapons);
    weapons.clear();
}

void MainWindow::setupWeapons() {
    // Add child classes to the list.
    weapons.append( new SCARL());
    // Add more if needed
}

void MainWindow::populateWeaponButtons() {
    for (int i = 0; i < weapons.size(); ++i) {
        QPushButton *button = new QPushButton(weapons[i]->getName());
        button->setIcon(QIcon(weapons[i]->getImagePath()));
        button->setIconSize(QSize(64, 64)); // Adjust as necessary

        connect(button, &QPushButton::clicked, this, [ this, i]() {
            openWeaponDetails(weapons[i]->getName());
        });

        gridLayout->addWidget(button, i / 3, i % 3); // Arrange in a grid (3 columns)
    }
}

void MainWindow::openWeaponDetails(const QString &weaponName) {
    for (const Weapon* weapon : weapons) {
        if (weapon->getName() == weaponName) {
            // Open explosive view

            QMessageBox::information(this, "Weapon Details",
                                     "Weapon: " + weapon->getName() +
                                    "\nFeature: " + weapon->getSpecialFeature());

            // Create a dialog for the exploded view
            QDialog explodedViewDialog(this);
            explodedViewDialog.setWindowTitle(weapon->getName() + " - Exploded View");

            QVBoxLayout *layout = new QVBoxLayout(&explodedViewDialog);

            QLabel *imageLabel = new QLabel(&explodedViewDialog);
            QPixmap pixmap(weapon->getExplodedViewPath());

            if (pixmap.isNull()) {
                QMessageBox::warning(this, "Error", "Failed to load exploded view image.");
                return;
            }

            imageLabel->setPixmap(pixmap);
            imageLabel->setScaledContents(true);
            imageLabel->setFixedSize(800, 800); // Adjust size as needed

            layout->addWidget(imageLabel);
            explodedViewDialog.setLayout(layout);

            // Show the dialog modally
            explodedViewDialog.exec();

            return;

        }
    }
     QMessageBox::warning(this, "Weapon Not Found", "The specified weapon was not found.");
}

