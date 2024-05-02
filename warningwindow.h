#ifndef WARNINGWINDOW_H
#define WARNINGWINDOW_H

#include <QDialog>

namespace Ui {
class warningWindow;
}

class warningWindow : public QDialog
{
    Q_OBJECT

public:
    explicit warningWindow(QWidget *parent = nullptr);
    ~warningWindow();

    void setErrorDescription(const QString& text);

private:
    Ui::warningWindow *ui;
};

#endif // WARNINGWINDOW_H
