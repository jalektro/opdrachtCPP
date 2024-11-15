#include "mainwindow.h"
#include <QIcon>
#include <QLabel>
#include <QDebug>

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
        QString thumbnailPath = ":/images/images/" +weaponList[i] + ".jpg";
        weaponButton->setIcon(QIcon(thumbnailPath));
        weaponButton->setIconSize(QSize(100,100));
        weaponButton->setFixedSize(100,100); //set button size

        //  Store the weapon ID in the button's property for retrieval
        weaponButton->setProperty("weaponID",weaponList[i]);

        //connect the button click to open weapon details slot
        connect(weaponButton, &QPushButton::clicked,this, &MainWindow::openWeaponDetails);

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
void MainWindow::openWeaponDetails(){
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if(!button) return;

    //  Retrieve the weapon ID stored in the button's property
    QString weaponID = button->property("weaponID").toString();
    qDebug() << "Opening details for weapon:" << weaponID;

    // TODO: open a new windows or dialog showing the weapon's exploded view
    //for now, just print the debug output
}
