#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createtask.h"
#include <QDateTime>
#include "taskwidgetitem.h"
#include <QListWidget>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    listWidget = ui->listWidget;

    QFile file("./tasks.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream readStream(&file);
        while (!readStream.atEnd()) {
            QString line = readStream.readLine();
            QStringList parts = line.split("/");
            if (parts.size() >= 5) {
                QListWidgetItem *item = new QListWidgetItem;

                // Создаем QWidget для хранения элементов
                QWidget *widget = new QWidget;
                QGridLayout *layout = new QGridLayout(widget);

                // Создаем QLabel для текста задания
                QLabel *taskLabel = new QLabel(parts[4]);
                taskLabel->setWordWrap(true);
                taskLabel->setFixedSize(200, 50);
                layout->addWidget(taskLabel, 0, 0);

                // Создаем QLabel для даты
                QLabel *dateLabel = new QLabel(parts[3]);
                dateLabel->setFixedSize(100, 25);
                layout->addWidget(dateLabel, 1, 0, Qt::AlignLeft | Qt::AlignBottom);

                // Создаем QCheckBox для выбора задачи
                QCheckBox *checkBox = new QCheckBox;
                checkBox->setFixedSize(25, 25);
                layout->addWidget(checkBox, 0, 1, Qt::AlignRight | Qt::AlignTop);

                // Создаем QLabel для сложности
                QLabel *difficultyLabel = new QLabel(parts[2]);
                difficultyLabel->setFixedSize(75, 25);
                layout->addWidget(difficultyLabel, 1, 1, Qt::AlignRight | Qt::AlignBottom);

                layout->setContentsMargins(5, 5, 5, 5);

                widget->setLayout(layout);
                item->setSizeHint(QSize(335, 75));
                ui->listWidget->addItem(item);
                ui->listWidget->setItemWidget(item, widget);
            } else {
                qDebug() << "Error" << line;
            }
        }
        file.close();
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
