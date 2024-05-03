#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "warningwindow.h"
#include "createtask.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <tasks.h>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->setMovable(false);

    Tasks tasks;
    tasks.reloadTasksFromFile(ui->listWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actioncreate_triggered()
{
    createTask w(this, ui->listWidget);
    w.setWindowTitle("Create task");
    w.setModal(true);
    w.exec();
}
