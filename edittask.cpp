#include "edittask.h"
#include "ui_edittask.h"

editTask::editTask(QWidget *parent, int taskNumber)
    : QDialog(parent)
    , ui(new Ui::editTask)
    , m_taskNumber(taskNumber)
{
    ui->setupUi(this);
    qDebug() << taskNumber;
}

editTask::~editTask()
{
    delete ui;
}
