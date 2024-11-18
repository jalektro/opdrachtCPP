#include "explosiveview.h"
#include <QPixmap>
#include <QMessageBox>


ExplosiveView::ExplosiveView(const QString &weaponID, QWidget *parent)
    : QWidget(parent)
{
    setupUI(weaponID);
}

ExplosiveView::~ExplosiveView()  {}

QVBoxLayout *ExplosiveView::getLayout() const
{
    return layout;
}

void ExplosiveView::setupUI(const QString &weaponID)
{
    layout = new QVBoxLayout(this);

    //set explosive view with numbers
    weaponImageLabel = new QLabel(this);
    QPixmap weaponExplosiveView(":/explosiveView/" + weaponID + ".jpg");
    weaponImageLabel->setPixmap(weaponExplosiveView);
    weaponImageLabel->setAlignment(Qt::AlignCenter);

    //configure search bar
    partNumberLineEdit = new QLineEdit(this);
    partNumberLineEdit->setPlaceholderText("Enter part nulber");

    //add search button
    searchButton = new QPushButton("Search", this);
    connect(searchButton, &QPushButton::clicked, this, &ExplosiveView::onSearchButtonClicked);

    // add widgets for layout
    layout->addWidget(weaponImageLabel);
    layout->addWidget(partNumberLineEdit);
    layout->addWidget(searchButton);

    setLayout(layout);
}

void ExplosiveView::onSearchButtonClicked()
{
    QString partNumber = partNumberLineEdit->text();

    if (partNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a part number.");
        return;
    }

    // Here should come send to server to search for the partnumber and return the NSN from the PDF
    QMessageBox::information(this, "Search Result", "Searching for NSN for part: " + partNumber);

}
