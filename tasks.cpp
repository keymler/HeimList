#include "tasks.h"
#include "qfile.h"

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
        return true;
    }
    else
    {
        return false;
    }
}
