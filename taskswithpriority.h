#ifndef TASKSWITHPRIORITY_H
#define TASKSWITHPRIORITY_H

#include "tasks.h"

class TaskWithPriority : public Tasks
{
public:
    TaskWithPriority();
    TaskWithPriority(int number, int status, const QString &difficulty, const QDateTime &dateTime, const QString &text, int priority);
    virtual ~TaskWithPriority();
    int getPriority() const;
    void setPriority(int priority);
    bool saveTaskToFileWithPriority(int number, int status, const QString& difficulty, const QDateTime& dateTime, const QString& text, int priority);
    void reloadTasksFromFileWithPriority(QListWidget* listWidget);
    void createTaskItemWithPriority(QListWidget* listWidget, int number, int status, const QString& difficulty, const QDateTime& dateTime, const QString& text, int priority);

protected:
    int priority;
};

#endif // TASKSWITHPRIORITY_H
