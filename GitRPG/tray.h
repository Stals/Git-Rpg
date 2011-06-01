#ifndef TRAY_H
#define TRAY_H

#include <QSystemTrayIcon>
#include <QIcon>
#include <QAction>
#include <QMenu>

#include "eventqueue.h"
class Tray{
public:
    Tray();//������ ������ � ����, � ��������� ���� ����� ����� ���� �������� ��� ���������� ����������
    void showEvent();//���������� ���� ��������� �� eventQueue , ���� �� �� ������.

    QSystemTrayIcon* tray;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *quitAction;
    QMenu *systemTrayMenu;
};
#endif
