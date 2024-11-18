#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
   explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private slots:
    void openWeaponDetails(QString weaponID);  //slot to handle button clicks

   private:
    QWidget *centralWidget; // Central widget of main window
    QGridLayout *gridLayout;    //Layout to arrange weapon buttons
    QVector<QString> weaponList; //list of weapon ID's
    void setupWeapons();    // function to populate the grid with weapon buttons
};

#endif // MAINWINDOW_H
