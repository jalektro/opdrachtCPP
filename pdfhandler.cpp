#include "pdfhandler.h"
#include <QVBoxLayout>
#include <QMessageBox>

pdfHandler::pdfHandler( QWidget* parent )
    :QDialog( parent), pdfDocument( new QPdfDocument( this )), pdfView( new QPdfView( this )) {
    QVBoxLayout* layout = new QVBoxLayout( this );
    pdfView->setDocument( pdfDocument );
    layout->addWidget( pdfView );
    setLayout( layout );
    //setWindowTitle("PDF Viewer");
    resize( 1000, 1000 );
}

pdfHandler::~pdfHandler () {
    delete pdfDocument;
}

bool pdfHandler::loadPdf( const QString& pdfPath ) {
    if( pdfDocument->load( pdfPath ) == QPdfDocument::Error::FileNotFound ) {
        QMessageBox::warning(this, "Error", "Failed to load PDF: " + pdfPath);
        return false;
    }
    return true;
}

bool pdfHandler::searchAndOpenPage( const QString& term ) {
    if (pdfDocument->status() != QPdfDocument::Status::Ready) {
        QMessageBox::warning(this, "Error", "PDF is not ready.");
        return false;
    }

    int pageFound = -1;
    for (int i = 0; i < pdfDocument->pageCount(); ++i) {
        QString pageText = pdfDocument->page(i)->text();
        if (pageText.contains(term)) {
            pageFound = i;
            break;
        }
    }

    if (pageFound == -1) {
        QMessageBox::information(this, "Not Found", "Term '" + term + "' not found in the PDF.");
        return false;
    }

    pdfView->pageNavigator()->jump(pageFound);
    return true;
}

void pdfHandler::showPdf () {
    exec();
}
