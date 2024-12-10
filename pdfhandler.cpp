#include "pdfhandler.h"
#include "qscrollbar.h"
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
  // no manual delete needed
}

bool pdfHandler::loadPdf( const QString& pdfPath ) {
    if( pdfDocument->load( pdfPath ) == QPdfDocument::Error::FileNotFound ) {
        QMessageBox::warning( this, "Error", "Failed to load PDF: " + pdfPath);
        return false;
    }
    return true;
}

bool pdfHandler::searchAndOpenPage( const QString& term ) {
    if (pdfDocument->status() != QPdfDocument::Status::Ready) {
        QMessageBox::warning( this, "Error", "PDF is not ready.");
        return false;
    }

    QPdfSearchModel pdfSearchModel( this );
    pdfSearchModel.setDocument( pdfDocument );
    pdfSearchModel.setSearchString( term );

    if ( pdfSearchModel.rowCount( QModelIndex()) == 0) {
        QMessageBox::information( this, "Not Found", "Term '" + term + "' not found in the PDF.");
    return false;
    }

    // Retrieve the first search result
    QModelIndex firstResult = pdfSearchModel.index(0, 0);
    QVariant resultData = pdfSearchModel.data(firstResult, Qt::UserRole);
    // Check the result type
    if (!resultData.isValid() || !resultData.canConvert<QVariantList>()) {
        QMessageBox::warning(this, "Error", "Failed to retrieve valid search result.");
        return false;
    }

    // Extract items from the result
    QVariantList resultList = resultData.toList();
    if (resultList.size() != 2) {
        QMessageBox::warning(this, "Error", "Unexpected result format.");
        return false;
    }

    int pageFound = resultList[0].toInt(); // First item: page number
    QPointF position = resultList[1].toPointF(); // Second item: position on the page

    // Debugging information
    qDebug() << "Search term found on page:" << pageFound << "at position:" << position;

    // Navigate to the page
    if (pageFound < 0 || pageFound >= pdfDocument->pageCount()) {
        QMessageBox::warning(this, "Error", "Invalid page number found.");
        return false;
    }

    // Scroll to the specific position on the page
    pdfView->verticalScrollBar()->setValue(pageFound * pdfView->viewport()->height());
    // Optionally adjust for the position within the page

    return true;
}
void pdfHandler::showPdf () {
    exec();
}
