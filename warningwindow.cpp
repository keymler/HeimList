#include "warningwindow.h"
#include "ui_warningwindow.h"

warningWindow::warningWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::warningWindow)
{
    ui->setupUi(this);
}

warningWindow::~warningWindow()
{
    delete ui;
}

void warningWindow::setErrorDescription(const QString& text)
{
    ui->errorDiscription->setText(text);
}
