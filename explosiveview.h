#ifndef EXPLOSIVEVIEW_H
#define EXPLOSIVEVIEW_H

#include <qwidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class ExplosiveView : public QWidget
{
        Q_OBJECT
public:
  explicit ExplosiveView(const QString &weaponID, QWidget *parent = nullptr);
    ~ExplosiveView();

  QVBoxLayout *getLayout() const;

  private:
    QLabel *weaponImageLabel;
    QLineEdit *partNumberLineEdit;
    QPushButton *searchButton;
    QVBoxLayout *layout;

    void setupUI(const QString &weaponId);

private slots:
    void onSearchButtonClicked();

};

#endif // EXPLOSIVEVIEW_H
