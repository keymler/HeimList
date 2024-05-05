#include "tasks.h"
#include "warningwindow.h"

Tasks::Tasks() {

}

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
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString existingContent = file.readAll();
        file.close();
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream writeStream(&file);
            QString formattedDateTime = dateTime.toString("dd.MM.yyyy HH:mm");

            writeStream << QString("%1/%2/%3/%4/%5").arg(number).arg(status).arg(difficulty).arg(formattedDateTime).arg(text) << Qt::endl;
            writeStream << existingContent;

            file.close();
            return true;
        }
    }
    return false;
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

    QLabel *difficultyLabel = new QLabel(difficulty);
    difficultyLabel->setFixedSize(50, 25);
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


void Tasks::reloadTasksFromFile(QListWidget* listWidget)
{
    qDebug() << "asfuhid";
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
                continue;
            }
            int number = parts[0].toInt();
            int status = parts[1].toInt();
            QString difficulty = parts[2];
            QDateTime dateTime = QDateTime::fromString(parts[3], "dd.MM.yyyy HH:mm");
            QString text = parts[4];
            createTaskItem(listWidget, number, status, difficulty, dateTime, text);
        }
        file.close();
    } else {
        warningWindow w;
        w.setErrorDescription("File doesnt open");
        w.setModal(true);
        w.exec();
    }
}


bool Tasks::removeTaskFromFile(int taskNumber)
{
    QFile file("./tasks.txt");
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QStringList lines;
        QTextStream readStream(&file);
        while (!readStream.atEnd()) {
            QString line = readStream.readLine();
            QStringList parts = line.split("/");
            int number = parts[0].toInt();
            if (number != taskNumber) {
                lines << line;
            }
        }
        file.close();

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream writeStream(&file);
            writeStream << lines.join("\n");
            file.close();
            return true;
        }
    }
    return false;
}
