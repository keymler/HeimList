#ifndef TASKS_H
#define TASKS_H

#include <QString>
#include <QDateTime>
#include <QListWidget>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>

class Tasks
{
public:
    Tasks();
    Tasks(int number, int status, const QString &difficulty, const QDateTime &dateTime, const QString &text);
    virtual ~Tasks();
    int getNumber() const;
    int getStatus() const;
    QString getDifficulty() const;
    QDateTime getDateTime() const;
    QString getText() const;

    virtual QString toString() const;

    bool saveTaskToFile(int number, int status, const QString& difficulty, const QDateTime& dateTime, const QString& text);
    void createTaskItem(QListWidget* listWidget, int number, int status, const QString& difficulty, const QDateTime& dateTime, const QString& text);
    void reloadTasksFromFile(QListWidget* listWidget);
    bool removeTaskFromFile(int taskNumber);

protected:
    int number;
    int status;
    QString difficulty;
    QDateTime dateTime;
    QString text;
};

#endif // TASKS_H
