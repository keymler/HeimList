#ifndef EDITTASK_H
#define EDITTASK_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include "mainwindow.h"


namespace Ui {
class editTask;
}

class editTask : public QDialog
{
    Q_OBJECT

public:
    explicit editTask(QWidget *parent = nullptr, int taskNumber = 1, QListWidget *listWidget = nullptr);
    ~editTask();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::editTask *ui;
    int m_taskNumber;
    QListWidget *m_listWidget;
};

#endif // EDITTASK_H
