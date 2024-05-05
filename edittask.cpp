#include "edittask.h"
#include "ui_edittask.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <tasks.h>
#include <QFontDatabase>
#include "warningwindow.h"

editTask::editTask(QWidget *parent, int taskNumber, QListWidget *listWidget)
    : QDialog(parent)
    , ui(new Ui::editTask)
    , m_taskNumber(taskNumber)
    , m_listWidget(listWidget)
{
    ui->setupUi(this);

    QFile file("./tasks.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream readStream(&file);
        readStream.seek(0);
        while (!readStream.atEnd()) {
            QString line = readStream.readLine();
            QStringList parts = line.split("/");
            int currentNumber = parts[0].toInt();
            if (taskNumber == currentNumber) {
                if (parts.size() < 5) {
                    qDebug() << "Invalid line format: " << line;
                    continue;
                }
                QString difficulty = parts[2];
                QDateTime dateTime = QDateTime::fromString(parts[3], "dd.MM.yyyy HH:mm");
                QString text = parts[4];

                ui->lineEdit->setText(text);
                ui->dateTimeEdit->setDateTime(dateTime);
                ui->difficultyEdit->setCurrentText(difficulty);
            }
        }
        file.close();
    } else {
        warningWindow w;
        w.setErrorDescription("File doesnt open");
        w.setModal(true);
        w.exec();
    }



}

editTask::~editTask()
{
    delete ui;
}

void editTask::on_saveButton_clicked()
{
    QString taskText = ui->lineEdit->text();
    QDateTime taskDateTime = ui->dateTimeEdit->dateTime();
    QString taskDifficulty = ui->difficultyEdit->currentText();

    Tasks tasks;
    tasks.removeTaskFromFile(m_taskNumber);

    tasks.saveTaskToFile(m_taskNumber, 0, taskDifficulty, taskDateTime, taskText);

    tasks.reloadTasksFromFile(m_listWidget);

    close();
}


void editTask::on_cancelButton_clicked()
{
    close();
}

