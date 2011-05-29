#include "tray.h"

Tray::Tray(){
    tray=new QSystemTrayIcon();
    tray->setIcon(QIcon("images/tray.png"));
    tray->show();
}
void Tray::showIcon(){

    tray->showMessage("11","22");



}
