#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <map>
#include <QMainWindow>
#include <QTimer>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
friend class Watcher;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer *minusTimer;
    QTimer *plusTimer;
    QTimer *jointTimer;
    void func();
    void displayStats();//оборажает характеристике ёзера на форме.
    std::pair<int,int> changedExp();//читает файл Stals, и если в нЄм есть изменени€ по кол-ву опыта, тогда возвращает true

private:
    Ui::MainWindow *ui;

private slots:
    void increaseJoint();
    void increasePlus();
    void increaseMinus();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
