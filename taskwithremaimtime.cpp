#include "taskwithremainingtime.h"

TaskWithRemainingTime::TaskWithRemainingTime(int number, int status, const QString& difficulty, const QDateTime& dateTime, const QString& text)
    : Tasks(number, status, difficulty, dateTime, text), dateTime(dateTime) // Измененное имя переменной
{
}

QString TaskWithRemainingTime::getRemainingTime() const
{
    qint64 remainingTime = dateTime.secsTo(QDateTime::currentDateTime());
    QTime remainingTimeTime = QTime::fromMSecsSinceStartOfDay(remainingTime * 1000);
    return remainingTimeTime.toString("hh:mm:ss");
}

QString TaskWithRemainingTime::toString() const
{
    QString formattedDateTime = dateTime.toString("dd.MM.yyyy HH:mm"); // Измененное имя переменной
    return QString("%1/%2/%3/%4/%5 (Remaining time: %6)").arg(number).arg(status).arg(difficulty).arg(formattedDateTime).arg(text).arg(getRemainingTime());
}

