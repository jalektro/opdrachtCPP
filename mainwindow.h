#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include "weapon.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openWeaponDetails(const QString &weaponName);  //slot to handle button clicks

private:
    QWidget *centralWidget; // Central widget of main window
    QGridLayout *gridLayout;    //Layout to arrange weapon buttons
    QVector<Weapon*> weapons;

    void setupWeapons();    // function to populate the grid with weapon buttons
    void populateWeaponButtons();
};

#endif // MAINWINDOW_H
