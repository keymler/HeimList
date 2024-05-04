#ifndef EDITTASK_H
#define EDITTASK_H

#include <QDialog>

namespace Ui {
class editTask;
}

class editTask : public QDialog
{
    Q_OBJECT

public:
    explicit editTask(QWidget *parent = nullptr, int taskNumber = 1 );
    ~editTask();

private:
    Ui::editTask *ui;
    int m_taskNumber;
};

#endif // EDITTASK_H
