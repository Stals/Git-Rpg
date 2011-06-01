#include "tray.h"

Tray::Tray(){
    tray=new QSystemTrayIcon();
    tray->setIcon(QIcon("images/tray.png"));

    minimizeAction = new QAction("&Minimize", tray);
    maximizeAction = new QAction("Maximize",tray);
    quitAction=new QAction("&Quit",tray);
    systemTrayMenu = new QMenu(tray->tr("tray"));

    systemTrayMenu->addAction(maximizeAction);
    systemTrayMenu->addAction(minimizeAction);
    systemTrayMenu->addSeparator();
    systemTrayMenu->addAction(quitAction);

    tray->setContextMenu(systemTrayMenu);


    this->tray->show();
    this->systemTrayMenu->show();
}
void Tray::showEvent(){
    if(eQueue.empty()!=true){
	eventPair pair;
	pair=eQueue.pop();
	std::string type;
	switch (pair.eType){
	case levelUp:
	    type="Level Up!";
	    break;
	case  achievement:
	    type="New Achievement!";
	    break;
	case notification:
	    type="";
	    break;

	}


	tray->showMessage(type.c_str(),pair.message.c_str());

    }

}
