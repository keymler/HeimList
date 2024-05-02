#include "createtask.h"
#include "ui_createtask.h"
#include "warningwindow.h"
#include <QTextStream>
#include <tasks.h>

createTask::createTask(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::createTask)
{
    ui->setupUi(this);

    QFile file("./tasks.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream readStream(&file);
        while (!readStream.atEnd()) {
            QString line = readStream.readLine();
            QStringList parts = line.split("/");
            int taskNumber = parts[0].toInt();
            if (taskNumber > maxTaskNumber) {
                maxTaskNumber = taskNumber;
            }
        }
        file.close();
    }
}

createTask::~createTask()
{
    delete ui;
}

void createTask::on_saveButton_clicked()
{
    if (!ui->lineEdit->text().isEmpty() &&
        !ui->dateTimeEdit->text().isEmpty() &&
        ui->difficultyEdit->currentIndex() != -1)
    {
        int newTaskNumber = ++maxTaskNumber;
        int status = 1;
        QString difficulty = ui->difficultyEdit->currentText();
        QDateTime dateTime = ui->dateTimeEdit->dateTime();
        QString text = ui->lineEdit->text();

        Tasks task(newTaskNumber, status, difficulty, dateTime, text);
        if (task.saveTaskToFile(newTaskNumber, status, difficulty, dateTime, text))
        {
            close();
        }
        else
        {
            warningWindow w;
            w.setErrorDescription("Failed to save the task to a file");
            w.setModal(true);
            w.exec();
        }
    }
    else
    {
        warningWindow w;
        w.setErrorDescription("Not all fields are filled in");
        w.setModal(true);
        w.exec();
    }
}

void createTask::on_cancelButton_clicked()
{
    close();
}

