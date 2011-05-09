#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void func();
    void displayStats();//оборажает характеристике Юзера на форме.
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
