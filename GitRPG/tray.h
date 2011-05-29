#ifndef TRAY_H
#define TRAY_H

#include <QSystemTrayIcon>
#include <QIcon>
#include "eventqueue.h"
class Tray{
public:
    Tray();
    void showEvent();
     QSystemTrayIcon* tray;
};
#endif
