#include "explosiveview.h"
#include <QPixmap>
#include <QMessageBox>
#include <QPdfDocument>
#include <QPdfPageNavigator>


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

    QPdfDocument *pdfDocument = new QPdfDocument(this);
    pdfDocument->load("C:/01. Bewapening/02. Lichte bewapening/15. MAG 7,62mm/1. SNL/MAG-SNL-NF.pdf");
    pdfViewer = new QPdfView(this);
    pdfViewer->setDocument(pdfDocument);

    pdfViewer->pageNavigator()->jump(10, {100,100});

    //set explosive view with numbers
    weaponImageLabel = new QLabel(this);
    QPixmap weaponExplosiveView(":/explosiveView/" + weaponID + ".jpg");
    weaponImageLabel->setPixmap(weaponExplosiveView);
    weaponImageLabel->setAlignment(Qt::AlignCenter);

    //configure search bar
    partNumberLineEdit = new QLineEdit(this);
    partNumberLineEdit->setPlaceholderText("Enter part number");

    //add search button
    searchButton = new QPushButton("Search", this);
    connect(searchButton, &QPushButton::clicked, this, &ExplosiveView::onSearchButtonClicked);

    // add widgets for layout
    // layout->addWidget(weaponImageLabel);
    layout->addWidget(pdfViewer);
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
