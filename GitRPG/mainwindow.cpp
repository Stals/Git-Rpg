#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include "eventqueue.h"
#include <fstream>
#include <windows.h>
#include "tray.h"




static User user;


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //TODO: Может при отображении старых статов тоже делать это таймером, всмысле полоска едет и опыт заполняется, от нуля до того что щас( но не меняя уровень). После этого если есть файл Stals с изменениями, можно выдать сообщение в трей типо, о новые данные, щас я всё сделаю и начинает заполнять...
    //!!!Ну как минимум после включения если есть, то нужно давать сообщения о том что я вижу что есть новое( наверно это просто в func записать, чтобы он выдавать сообщение в трей каждый раз когда он начинает увеличивать на форме.)

    progressBarTimer = new QTimer(this);
    connect(progressBarTimer, SIGNAL(timeout()),this,SLOT(increaseAll()));

    displayStats();

    setFixedSize(width(), height());//Не позволяет изменять размер окна.

    connect(tray.minimizeAction,SIGNAL(triggered()),this,SLOT(hide()));//hides window if minimize in a tray menu was pressed
    connect(tray.maximizeAction,SIGNAL(triggered()),this,SLOT(show()));//shows window if maximize in a tray menu was pressed
    connect(tray.quitAction,SIGNAL(triggered()),this,SLOT(close()));//closes application if quit in a tray menu was pressed
    connect(tray.tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
	    this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    tray.tray->setToolTip(QString(user.getStats().c_str()));

    func();//при старте запускается func() чтобы проверить небыло ли изменений пока программа была выключена (когда она работает этим занимается fileSystemWatchr)

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
	break;
    case QSystemTrayIcon::DoubleClick:
	if(this->isHidden()==true){
	    this->show();
	    this->activateWindow();
	}else{
	    this->hide();
	}
	break;
    case QSystemTrayIcon::MiddleClick:
	eQueue.push(notification,user.getStats());
	tray.showEvent();
	break;
    default:
	break;
    }
}

void MainWindow::func(){
    ui->label->setText("ok");
    //Если измения в опыте влияют начать увеличение



    if(getChangedExp()){//если были изменения
	//! TODO: может стоит писать об изменениях Joint тоже?
	eQueue.push(progress,"Insertions: "+QString::number(user.newExp.first-user.plus.exp).toStdString()+"\n"+
		    "Delitions: "+QString::number(user.newExp.second-user.minus.exp).toStdString());
	tray.showEvent();


        //тогда мы должны стартовать таймеры
        ui->label->setText("StartTimers");
	progressBarTimer->start(1);

    }

    displayStats();

    //+ внутри таймеров могут появиться сообщения в трей, так что нужно начать таймер который отображает их.
    //! TODO может можно сделать эксепшн типа события, которое может поймать таймер и только тогда показывать сообщения  в трей
    //(чтобы он проверял не каждые N секунд есть ли что в queue, а делал если туда что-то добавилось)

}
void MainWindow::displayStats(){

    ui->userName->setText(user.name.c_str());

    //Joint
    ui->jointLvl->setText("Joint Level "+QString::number(user.joint.lvl));
    ui->jointExp->setText("[ "+QString::number(user.joint.exp-user.joint.lastExp)+" / "+QString::number(user.joint.maxExp-user.joint.lastExp)+" ]");
    ui->jointBar->setValue(user.joint.exp-user.joint.lastExp);
    ui->jointBar->setMaximum(user.joint.maxExp-user.joint.lastExp);
    //Plus
    ui->plusLvl->setText("Insertions (+) Level "+QString::number(user.plus.lvl));
    ui->plusExp->setText("[ "+QString::number(user.plus.exp-user.plus.lastExp)+" / "+QString::number(user.plus.maxExp-user.plus.lastExp)+" ]");
    ui->plusBar->setValue(user.plus.exp-user.plus.lastExp);
    ui->plusBar->setMaximum(user.plus.maxExp-user.plus.lastExp);
    //Minus
    ui->minusLvl->setText("Deleitions  (-) Level "+QString::number(user.minus.lvl));
    ui->minusExp->setText("[ "+QString::number(user.minus.exp-user.minus.lastExp)+" / "+QString::number(user.minus.maxExp-user.minus.lastExp)+" ]");
    ui->minusBar->setValue(user.minus.exp-user.minus.lastExp);
    ui->minusBar->setMaximum(user.minus.maxExp-user.minus.lastExp);

}
bool MainWindow::getChangedExp(){
    //Читаем файл Stals и сравниваем с тем что есть в User
    //Для этого нам нужно сложить все минусы и плюсы из Stals
    int plus=0;
    int minus=0;
    int numberOfProjects;
    std::string projectName;
    int buf;

    std::string p;
    std::ifstream f("Stals");

    f>>numberOfProjects;
    for(int i=0;i<numberOfProjects;++i){
	std::getline(f,projectName);
	std::getline(f,projectName);
        f>>buf; plus+=buf;
        f>>buf; minus+=buf;
    }



    if((plus>user.plus.exp)||(minus>user.minus.exp)){
	user.newExp.first=plus;
	user.newExp.second=minus;
	return true;

    }else{
	return false;


    }

}

void MainWindow::increaseAll(){

    while((user.plus.exp<user.newExp.first)||(user.minus.exp<user.newExp.second)||(user.joint.exp<(user.newExp.first+user.newExp.second))){
	if(user.joint.exp<(user.newExp.first+user.newExp.second)){
            ++user.joint.exp;
            ui->jointBar->setValue(user.joint.exp);
        }
	if(user.plus.exp<user.newExp.first){
            ++user.plus.exp;
            ui->plusBar->setValue(user.plus.exp);
        }
	if(user.minus.exp<user.newExp.second){
	    //сравниваем то что осталось добавить с общей разницей из newExp
	    //! TODO может вычислять при получении и потом хранить в юзер , также как и newExp?(чтобы не вычислять каждый раз
	    const double balance=(double)user.newExp.second/(double)user.newExp.first;
	    if((user.newExp.first-user.plus.exp)!=0){
		if(balance<=((double)(user.newExp.second-user.minus.exp)/(double)(user.newExp.first-user.plus.exp))){
		    ++user.minus.exp;
		    ui->minusBar->setValue(user.minus.exp);
		}
	    }
        }

	user.checkForLvls();
	tray.showEvent();
	displayStats();
	Sleep(5);
    }
    user.saveStats();//После всех таймеров сохраняем статы
    progressBarTimer->stop();

}

//! свой слип у каждой статистики в зависимости от того сколько еще осталось добавить
//! мне просто не понятно что делать если первый раз человек запускает и у него 4 тыщи строк, или первый раз и у него 100 строк, скорость должна быть примерно одинаковой,чтобы всё это заполнилось
void MainWindow::on_pushButton_clicked()
{
    user.joint.exp+=2;
    ++user.plus.exp;
    ++user.minus.exp;
    user.checkForLvls();
    displayStats();

    tray.showEvent();

}
