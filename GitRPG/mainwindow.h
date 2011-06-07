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

    void func();//������� ���������� ����� ��������� ��������� � ���� ��� ���� ���������� �� �� �����
    void displayStats();//��������� �������������� ������������ �� �����.
    bool getChangedExp();//������ ���� Stals, � ���� � �� ���� ��������� �� ���-�� �����, ����� ������� �� � user.newExp � ���������� true

private:
    Ui::MainWindow *ui;
    Tray tray;
private slots:

    void iconActivated(QSystemTrayIcon::ActivationReason reason);//���������� ��� ����� �� ������ � ����
    void increaseAll(); //������� ������������ �������� ��� ������������ ���������� �����

    void changeEvent (QEvent *e);//������ �� event'��� � ��� ������������ ���� ������������ ��� � tray
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
