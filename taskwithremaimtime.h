#ifndef TASKWITHREMAININGTIME_H
#define TASKWITHREMAININGTIME_H

#include "tasks.h"

class TaskWithRemainingTime : public Tasks
{
public:
    TaskWithRemainingTime(int number, int status, const QString& difficulty, const QDateTime& dateTime, const QString& text);
    QString getRemainingTime() const;
    QString toString() const override;

private:
    QDateTime dateTime;
};

#endif
