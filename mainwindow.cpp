#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "warningwindow.h"
#include "createtask.h"
#include "edittask.h"
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
    tasks.readScore(ui->score);
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

void MainWindow::on_actiondelete_triggered(bool checked)
{
    if (checked) {
        ui->listWidget->setStyleSheet("background-color: brown; color: white;");
        qDebug() << "Delete action activated";
    } else {
        ui->listWidget->setStyleSheet("background-color: rgb(255, 245, 165);");
        qDebug() << "Delete action deactivated";
    }
}

void MainWindow::updateWidgetStyleEdit(bool editMode)
{
    if (editMode) {
        ui->listWidget->setStyleSheet("background-color: rgb(199, 166, 0); color: white;");
        qDebug() << ("Edit action activated");
    } else {
        ui->listWidget->setStyleSheet("background-color: rgb(255, 245, 165);");
        qDebug() << ("Edit action deactivated");
    }
}
void MainWindow::on_actionedit_triggered(bool checked)
{
    updateWidgetStyleEdit(checked);
}

void MainWindow::updateWidgetStyleMarkAsDone(bool markAsDoneMode)
{
    if (markAsDoneMode) {
        ui->listWidget->setStyleSheet("background-color: rgb(25, 190, 80); color: white;");
        qDebug() << ("MarkAsDone action activated");
    } else {
        ui->listWidget->setStyleSheet("background-color: rgb(255, 245, 165);");
        qDebug() << ("MarkAsDone action deactivated");
    }
}
void MainWindow::on_actionmarkasdone_triggered(bool checked)
{
    updateWidgetStyleMarkAsDone(checked);
}



void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if (ui->actiondelete->isChecked()) {
        Tasks tasks;
        QWidget* itemWidget = ui->listWidget->itemWidget(item);
        QLabel* taskNumberLabel = itemWidget->findChild<QLabel*>("taskNumberLabel");
        int taskNumber = taskNumberLabel->text().toInt();

        if (tasks.removeTaskFromFile(taskNumber)) {
            qDebug() << "Task" << taskNumber << "removed successfully";
        } else {
            qDebug() << "Failed to remove task" << taskNumber;
        }
        tasks.reloadTasksFromFile(ui->listWidget);
    }

    if (ui->actionedit->isChecked()) {
        ui->actionedit->setChecked(false);
        updateWidgetStyleEdit(false);
        QWidget* itemWidget = ui->listWidget->itemWidget(item);
        QLabel* taskNumberLabel = itemWidget->findChild<QLabel*>("taskNumberLabel");
        int taskNumber = taskNumberLabel->text().toInt();

        editTask* editTaskDialog = new editTask(this, taskNumber, ui->listWidget);
        editTaskDialog->setWindowTitle("Edit task");
        editTaskDialog->exec();
        delete editTaskDialog;
    }

    if (ui->actionmarkasdone->isChecked()) {
        ui->actionmarkasdone->setChecked(false);
        updateWidgetStyleMarkAsDone(false);
        QWidget* itemWidget = ui->listWidget->itemWidget(item);
        QLabel* taskNumberLabel = itemWidget->findChild<QLabel*>("taskNumberLabel");
        QLabel* difficultyLabel = itemWidget->findChild<QLabel*>("difficultyLabel");
        int taskNumber = taskNumberLabel->text().toInt();
        QString difficulty = difficultyLabel->text();

        Tasks tasks;
        tasks.addScore(ui->score, taskNumber, 1, difficulty);
        tasks.removeTaskFromFile(taskNumber);
        tasks.reloadTasksFromFile(ui->listWidget);
        qDebug() << taskNumber;
        qDebug() << difficulty;
    }
}
