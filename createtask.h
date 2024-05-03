#ifndef CREATETASK_H
#define CREATETASK_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include "mainwindow.h"

namespace Ui {
class createTask;
}

class createTask : public QDialog
{
    Q_OBJECT

public:
    explicit createTask(QWidget *parent = nullptr, QListWidget *listWidget = nullptr);
    ~createTask();

private slots:
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::createTask *ui;
    int maxTaskNumber = 0;
    QListWidget *m_listWidget;
};

#endif // CREATETASK_H
