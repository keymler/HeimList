#include "taskswithpriority.h"
#include "warningwindow.h"


TaskWithPriority::TaskWithPriority() : Tasks(), priority(0)
{
}

TaskWithPriority::TaskWithPriority(int number, int status, const QString &difficulty, const QDateTime &dateTime, const QString &text, int priority)
    : Tasks(number, status, difficulty, dateTime, text), priority(priority)
{
}

TaskWithPriority::~TaskWithPriority()
{
}

int TaskWithPriority::getPriority() const
{
    return priority;
}

void TaskWithPriority::setPriority(int priority)
{
    this->priority = priority;
}

bool TaskWithPriority::saveTaskToFileWithPriority(int number, int status, const QString& difficulty, const QDateTime& dateTime, const QString& text, int priority)
{
    QFile file("./tasks.txt");
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString existingContent = file.readAll();
        file.close();
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream writeStream(&file);
            QString formattedDateTime = dateTime.toString("dd.MM.yyyy HH:mm");

            writeStream << QString("%1/%2/%3/%4/%5/%6").arg(number).arg(status).arg(difficulty).arg(formattedDateTime).arg(text).arg(priority) << Qt::endl;
            writeStream << existingContent;

            file.close();
            return true;
        }
    }
    return false;
}

void TaskWithPriority::createTaskItemWithPriority(QListWidget* listWidget, int number, int status, const QString& difficulty, const QDateTime& dateTime, const QString& text, int priority)
{
    QListWidgetItem *item = new QListWidgetItem;
    QWidget *widget = new QWidget;
    QGridLayout *layout = new QGridLayout(widget);

    QLabel *taskLabel = new QLabel(text);
    taskLabel->setWordWrap(true);
    taskLabel->setFixedSize(200, 30);
    layout->addWidget(taskLabel, 0, 0);

    QString dateTimeString = dateTime.toString();
    QLabel *dateLabel = new QLabel(dateTimeString);
    dateLabel->setFixedSize(150, 25);
    layout->addWidget(dateLabel, 1, 0, Qt::AlignLeft | Qt::AlignBottom);

    QLabel *priorityLabel = new QLabel("Priority: " + QString::number(priority));
    priorityLabel->setObjectName("priorityLabel");
    priorityLabel->setFixedSize(59, 30);
    if (priority == 1) {
        priorityLabel->setStyleSheet("QLabel { color: green; }");
    } else if (priority ==2) {
        priorityLabel->setStyleSheet("QLabel { color: rgb(66, 56, 0); }");
    } else if(priority == 3){
        priorityLabel->setStyleSheet("QLabel { color: red; }");
    }
    layout->addWidget(priorityLabel, 0, 2, Qt::AlignRight);

    QLabel *difficultyLabel = new QLabel(difficulty);
    difficultyLabel->setFixedSize(59, 25);
    difficultyLabel->setObjectName("difficultyLabel");
    layout->addWidget(difficultyLabel, 1, 2, Qt::AlignRight | Qt::AlignBottom);

    QLabel *taskNumberLabel = new QLabel(QString::number(number));
    taskNumberLabel->setObjectName("taskNumberLabel");
    taskNumberLabel->setVisible(false);
    layout->addWidget(taskNumberLabel, 0, 3, Qt::AlignRight);

    layout->setContentsMargins(5, 5, 5, 5);
    layout->setColumnStretch(1, 1);

    widget->setLayout(layout);

    item->setSizeHint(QSize(320, 70));
    listWidget->addItem(item);
    listWidget->setItemWidget(item, widget);

    QFrame *separator = new QFrame;
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    QListWidgetItem *separatorItem = new QListWidgetItem;
    listWidget->addItem(separatorItem);
    listWidget->setItemWidget(separatorItem, separator);
}

void TaskWithPriority::reloadTasksFromFileWithPriority(QListWidget* listWidget)
{
    listWidget->clear();
    QFile file("./tasks.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream readStream(&file);
        readStream.seek(0);
        while (!readStream.atEnd()) {
            QString line = readStream.readLine();
            QStringList parts = line.split("/");
            if (parts.size() < 5) {
                qDebug() << "Invalid line format: " << line;
            }
            int number = parts[0].toInt();
            int status = parts[1].toInt();
            QString difficulty = parts[2];
            QDateTime dateTime = QDateTime::fromString(parts[3], "dd.MM.yyyy HH:mm");
            QString text = parts[4];
            if(parts.size() == 5){
                createTaskItem(listWidget, number, status, difficulty, dateTime, text);
            }else if(parts.size() == 6){
                int priority = parts[5].toInt();
                createTaskItemWithPriority(listWidget, number, status, difficulty, dateTime, text, priority);
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


