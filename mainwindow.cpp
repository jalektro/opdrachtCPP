#include "mainwindow.h"
#include <QIcon>
#include <QLabel>
#include <QDebug>
#include "explosiveview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    centralWidget(new QWidget(this)),
    gridLayout(new QGridLayout()),
    weaponList({"SCAR-L","Weapon2","weapon3"})
{
    setCentralWidget(centralWidget);
    centralWidget->setLayout(gridLayout);
    setupWeapons(); //populate the grid with weapon buttons
}

MainWindow::~MainWindow(){}

void MainWindow::setupWeapons(){
    int row=0, column = 0;
    for(int i=0; i<weaponList.size();i++){
        QPushButton *weaponButton = new QPushButton(this);

        //set an icon for the weapon button
        QString thumbnailPath = ":/images/" +weaponList[i] + ".jpg";
        weaponButton->setIcon(QIcon(thumbnailPath));
        weaponButton->setIconSize(QSize(100,100));
        weaponButton->setFixedSize(100,100); //set button size

        //  Store the weapon ID in the button's property for retrieval
        weaponButton->setProperty("weaponID",weaponList[i]);

        //connect the button click to open weapon details slot
        connect(weaponButton, &QPushButton::clicked, this, [this, weaponButton]() {
            QString weaponID = weaponButton->property("weaponID").toString();
            openWeaponDetails(weaponID); // Pass the weapon ID
        });

        //  Add button to the grid layout
        gridLayout->addWidget(weaponButton, row, column);

        //move to the next row/column  change 3 to the number of columns
        column++;
        if(column>= 3) {
            column =0;
            row++;
        }
    }
}

//slot: open weapon details when a button is clicked
void MainWindow::openWeaponDetails(QString weaponID)
{
    // Create the explosive view for the selected weapon
    ExplosiveView *explosiveView = new ExplosiveView(weaponID, this);

    // Replace the central widget with the explosive view
    setCentralWidget(explosiveView);

    // Optionally: Add a "Back" button to return to the main grid
    QPushButton *backButton = new QPushButton("Back", explosiveView);
    explosiveView->getLayout()->addWidget(backButton);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        // Restore the original grid layout
        setCentralWidget(centralWidget);
    });
}
