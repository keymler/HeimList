#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actioncreate_triggered();
    void on_actiondelete_triggered(bool checked);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_actionedit_triggered(bool checked);
    void updateWidgetStyleEdit(bool editMode);

private:
    Ui::MainWindow *ui;
    QListWidget* listWidget;
};

#endif // MAINWINDOW_H
