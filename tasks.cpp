#include "tasks.h"
#include "qfile.h"
#include "ui_mainwindow.h"

Tasks::Tasks(int number, int status, const QString &difficulty, const QDateTime &dateTime, const QString &text)
    : number(number), status(status), difficulty(difficulty), dateTime(dateTime), text(text)
{

}

Tasks::~Tasks()
{
}

int Tasks::getNumber() const
{
    return number;
}

int Tasks::getStatus() const
{
    return status;
}

QString Tasks::getDifficulty() const
{
    return difficulty;
}

QDateTime Tasks::getDateTime() const
{
    return dateTime;
}

QString Tasks::getText() const
{
    return text;
}

QString Tasks::toString() const
{
    QString formattedDateTime = dateTime.toString("dd.MM.yyyy HH:mm");

    return QString("%1/%2/%3/%4/%5").arg(number).arg(status).arg(difficulty).arg(formattedDateTime).arg(text);
}

bool Tasks::saveTaskToFile(int number, int status, const QString& difficulty, const QDateTime& dateTime, const QString& text)
{
    QFile file("./tasks.txt");
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream writeStream(&file);
        QString formattedDateTime = dateTime.toString("dd.MM.yyyy HH:mm");
        writeStream << QString("%1/%2/%3/%4/%5").arg(number).arg(status).arg(difficulty).arg(formattedDateTime).arg(text) << Qt::endl;
        file.close();
        return 1;
    }
    else
    {
        return 0;
    }
}

void Tasks::createTaskItem(QListWidget* listWidget, int number, int status, const QString& difficulty, const QDateTime& dateTime, const QString& text)
{
    QListWidgetItem *item = new QListWidgetItem;

    QWidget *widget = new QWidget;
    QGridLayout *layout = new QGridLayout(widget);

    QLabel *taskLabel = new QLabel(text);
    taskLabel->setWordWrap(true);
    taskLabel->setFixedSize(200, 50);
    layout->addWidget(taskLabel, 0, 0);

    QString dateTimeString = dateTime.toString();
    QLabel *dateLabel = new QLabel(dateTimeString);
    dateLabel->setFixedSize(150, 25);
    layout->addWidget(dateLabel, 1, 0, Qt::AlignLeft | Qt::AlignBottom);

    QCheckBox *checkBox = new QCheckBox;
    checkBox->setFixedSize(25, 25);
    layout->addWidget(checkBox, 0, 1, Qt::AlignRight | Qt::AlignTop);

    QLabel *difficultyLabel = new QLabel(difficulty);
    difficultyLabel->setFixedSize(75, 25);
    layout->addWidget(difficultyLabel, 1, 1, Qt::AlignRight | Qt::AlignBottom);

    layout->setContentsMargins(5, 5, 5, 5);

    widget->setLayout(layout);
    item->setSizeHint(QSize(335, 75));
    listWidget->addItem(item);
    listWidget->setItemWidget(item, widget);
}
