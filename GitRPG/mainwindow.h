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
    bool getChangedExp();//читает файл Stals, и если в нём есть изменения по кол-ву опыта, тогда передаёт их в user.newExp и возвращает true

private:
    Ui::MainWindow *ui;
    Tray tray;
private slots:

    void iconActivated(QSystemTrayIcon::ActivationReason reason);//вызывается при клике на иконку в трее
    void increaseAll(); //Функция используется таймером для постепенного увеличения опыта

    void changeEvent (QEvent *e);//Следит за event'ами и при сворачивании окна минимизирует его в tray
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
