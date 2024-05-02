#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "warningwindow.h"
#include "createtask.h"
#include <QDateTime>
#include <QListWidget>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <tasks.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file("./tasks.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream readStream(&file);
        while (!readStream.atEnd()) {
            QString line = readStream.readLine();
            QStringList parts = line.split("/");

            int number = parts[0].toInt();
            int status = parts[1].toInt();
            QString difficulty = parts[2];
            QDateTime dateTime = QDateTime::fromString(parts[3], "dd.MM.yyyy HH:mm");
            QString text = parts[4];

            Tasks task(number, status, difficulty, dateTime, text);
            task.createTaskItem(ui->listWidget, number, status, difficulty, dateTime, text);
        }
        file.close();
    } else{
        warningWindow w;
        w.setErrorDescription("File doesnt open");
        w.setModal(true);
        w.exec();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actioncreate_triggered()
{
    createTask w;
    w.setModal(true);
    w.exec();
}
