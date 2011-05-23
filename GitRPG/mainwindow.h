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
    QTimer *progressBarTimer;

    void func();//������� ���������� ����� ��������� ��������� � ���� ��� ���� ���������� �� �� �����
    void displayStats();//��������� �������������� ������������ �� �����.
    std::pair<int,int> changedExp();//������ ���� Stals, � ���� � �� ���� ��������� �� ���-�� �����, ����� ���������� true

private:
    Ui::MainWindow *ui;

private slots:
    void increaseAll(); //������� ������������ �������� ��� ������������ ���������� �����

    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
