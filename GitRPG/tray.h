#ifndef TRAY_H
#define TRAY_H

#include <QSystemTrayIcon>
#include <QIcon>
#include <QAction>
#include <QMenu>

#include "eventqueue.h"
class Tray{
public:
    Tray();//—оздаЄт »конку в трее, и добавл€ет меню чтобы можно было свернуть или развернуть приложение
    void showEvent();//показывает одно сообщение из eventQueue , если он не пустой.

    QSystemTrayIcon* tray;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *quitAction;
    QMenu *systemTrayMenu;
};
#endif
