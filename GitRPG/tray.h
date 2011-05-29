#ifndef TRAY_H
#define TRAY_H

#include <QSystemTrayIcon>
#include <QIcon>

class Tray{
public:
    Tray();
    void showIcon();
     QSystemTrayIcon* tray;
};
#endif
