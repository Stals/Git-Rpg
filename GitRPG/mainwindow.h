#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <map>
#include <QMainWindow>
#include <QTimer>
#include "tray.h"
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
    QTimer *progressBarTimer;

    void func();//Функция вызывается чтобы проверить изменения и если они есть отобразить их на форме
    void displayStats();//оборажает характеристики Пользователя на форме.
    std::pair<int,int> changedExp();//читает файл Stals, и если в нём есть изменения по кол-ву опыта, тогда возвращает true

private:
    Ui::MainWindow *ui;
Tray tray;
private slots:
    void increaseAll(); //Функция используется таймером для постепенного увеличения опыта

    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
