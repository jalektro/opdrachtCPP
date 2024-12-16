#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QPdfSearchModel>
#include "mainwindow.h"
#include "pdfhandler.h"
#include "scarl.h"
#include "scarh.h"


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
     weapons.append( new SCARH());
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

            // Add search box
            QLineEdit *searchBox = new QLineEdit(&explodedViewDialog);
            searchBox->setPlaceholderText("Enter number/name to search in the PDF...");
            layout->addWidget(searchBox);

            // Add search button
            QPushButton *searchButton = new QPushButton("Search", &explodedViewDialog);
            layout->addWidget(searchButton);

            // Add back button
            QPushButton *backButton = new QPushButton("Back to Main Page", &explodedViewDialog);
            layout->addWidget(backButton);

            explodedViewDialog.setLayout(layout);

            // Back button logic
            connect(backButton, &QPushButton::clicked, [&]() {
                explodedViewDialog.close();
            });

            // PDF handler
            pdfHandler *pdfViewer = new pdfHandler(&explodedViewDialog);
            QString pdfPath = weapon->getPdfPath(); // Ensure the weapon has an associated PDF path

            if (!pdfViewer->loadPdf(pdfPath)) {
                QMessageBox::warning(this, "Error", "Failed to load the PDF for this weapon.");
                delete pdfViewer;
                return;
            }

            connect(searchButton, &QPushButton::clicked, [&]() {
                QString searchTerm = searchBox->text().trimmed();
                if (searchTerm.isEmpty()) {
                    QMessageBox::warning(&explodedViewDialog, "Input Error", "Please enter a number to search.");
                    return;
                }

                if (!pdfViewer->searchAndOpenPage(searchTerm)) {
                    QMessageBox::information(&explodedViewDialog, "Not Found", "Number '" + searchTerm + "' not found in the PDF.");
                } else {
                    pdfViewer->showPdf(); // Show the PDF with the search result
                }
            });
            // Show the dialog modally
            explodedViewDialog.exec();

            return;

        }
    }
     QMessageBox::warning(this, "Weapon Not Found", "The specified weapon was not found.");
}

