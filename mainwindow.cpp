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

        editTask* editTaskDialog = new editTask(this, taskNumber);
        editTaskDialog->exec();
        delete editTaskDialog;
    }
}





