#ifndef PDFHANDLER_H
#define PDFHANDLER_H

#include <QDialog>
#include <QString>
#include <QPdfDocument>
#include <QPdfView>
#include <QPdfPageNavigator>
#include <QPdfSearchModel>



class pdfHandler : public QDialog{
    Q_OBJECT

public:
    explicit pdfHandler(QWidget* parent = nullptr);
    ~pdfHandler();

    bool loadPdf(const QString& pdfPath);
    bool searchAndOpenPage(const QString& term);
    void showPdf();

private:
    QPdfDocument* pdfDocument;
    QPdfView* pdfView;
};

#endif // PDFHANDLER_H
