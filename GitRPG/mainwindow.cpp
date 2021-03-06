#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include "eventqueue.h"
#include <fstream>
#include <windows.h>
#include "tray.h"
#include <cmath>



static User user;


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //TODO: ����� ��� ����������� ������ ������ ���� ������ ��� ��������, ������� ������� ���� � ���� �����������, �� ���� �� ���� ��� ���( �� �� ����� �������). ����� ����� ���� ���� ���� Stals � �����������, ����� ������ ��������� � ���� ����, � ����� ������, ��� � �� ������ � �������� ���������...
    //!!!�� ��� ������� ����� ��������� ���� ����, �� ����� ������ ��������� � ��� ��� � ���� ��� ���� �����( ������� ��� ������ � func ��������, ����� �� �������� ��������� � ���� ������ ��� ����� �� �������� ����������� �� �����.)

    progressBarTimer = new QTimer(this);
    connect(progressBarTimer, SIGNAL(timeout()),this,SLOT(increaseAll()));

    eventTimer = new QTimer(this);
    connect(eventTimer,SIGNAL(timeout()),this,SLOT(showEvent()));
    eventTimer->start(1000);

    displayStats();

    setFixedSize(width(), height());//�� ��������� �������� ������ ����.

    connect(tray.minimizeAction,SIGNAL(triggered()),this,SLOT(hide()));//hides window if minimize in a tray menu was pressed
    connect(tray.maximizeAction,SIGNAL(triggered()),this,SLOT(show()));//shows window if maximize in a tray menu was pressed
    connect(tray.quitAction,SIGNAL(triggered()),this,SLOT(close()));//closes application if quit in a tray menu was pressed
    connect(tray.tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
	    this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    tray.tray->setToolTip(QString(user.getStats().c_str()));

    func();//��� ������ ����������� func() ����� ��������� ������ �� ��������� ���� ��������� ���� ��������� (����� ��� �������� ���� ���������� fileSystemWatchr)

}

MainWindow::~MainWindow()
{
    tray.tray->setVisible(false);
    delete ui;
}
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
	if(this->isHidden()==true){
	    this->showNormal();
	    this->activateWindow();
	}else{
	    this->hide();
	}
	break;

    case QSystemTrayIcon::DoubleClick:

	break;
    case QSystemTrayIcon::MiddleClick:
	break;
    default:
	break;
    }
}

void MainWindow::changeEvent (QEvent *e)
{
    if(e->type() == QEvent::WindowStateChange)
    {
	//Now check to see if the window is minimised
	if (isMinimized())
	{

	    QTimer::singleShot(250, this, SLOT(hide()));

	}
    }
}
void MainWindow::func(){

    //���� ������� � ����� ������ ������ ����������

    if(getChangedExp()){//���� ���� ���������
	//! TODO: ����� ����� ������ �� ���������� Joint ����?
	eQueue.push(progress,"Additions: "+QString::number(user.newExp.first-user.plus.exp).toStdString()+"\n"+
		    "Delitions: "+QString::number(user.newExp.second-user.minus.exp).toStdString());



	//����� �� ������ ���������� �������

	progressBarTimer->start(1);

    }

    displayStats();

    //+ ������ �������� ����� ��������� ��������� � ����, ��� ��� ����� ������ ������ ������� ���������� ��.
    //! TODO ����� ����� ������� ������� ���� �������, ������� ����� ������� ������ � ������ ����� ���������� ���������  � ����
    //(����� �� �������� �� ������ N ������ ���� �� ��� � queue, � ����� ���� ���� ���-�� ����������)

}
void MainWindow::displayStats(){

    ui->userName->setText(user.name.c_str());

    //Joint
    ui->jointLvl->setText("Joint Level "+QString::number(user.joint.lvl));
    ui->jointExp->setText("[ "+QString::number(user.joint.exp-user.joint.lastExp)+" / "+QString::number(user.joint.maxExp-user.joint.lastExp)+" ]");
    ui->jointBar->setValue(user.joint.exp-user.joint.lastExp);
    ui->jointBar->setMaximum(user.joint.maxExp-user.joint.lastExp);
    //Plus
    ui->plusLvl->setText("Additions (+) Level "+QString::number(user.plus.lvl));
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
    //������ ���� Stals � ���������� � ��� ��� ���� � User
    //��� ����� ��� ����� ������� ��� ������ � ����� �� Stals
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
	    //���������� �� ��� �������� �������� � ����� �������� �� newExp
	    //! TODO ����� ��������� ��� ��������� � ����� ������� � ���� , ����� ��� � newExp?(����� �� ��������� ������ ���


	    double allBalance=(double)user.newExp.second/(double)user.newExp.first;

	    double newBalance=(double)(user.newExp.second-user.minus.exp)/(double)(user.newExp.first-user.plus.exp);



	    if(allBalance<=newBalance){
		++user.minus.exp;
		ui->minusBar->setValue(user.minus.exp);
	    }

	}

	user.checkForLvls();

	displayStats();
	Sleep(5);
    }
    user.saveStats();//����� ���� �������� ��������� �����
    progressBarTimer->stop();
    tray.tray->setToolTip(QString(user.getStats().c_str()));//�������� ��������� ��� ��������� �� Tray
}

//! ���� ���� � ������ ���������� � ����������� �� ���� ������� ��� �������� ��������
//! ��� ������ �� ������� ��� ������ ���� ������ ��� ������� ��������� � � ���� 4 ���� �����, ��� ������ ��� � � ���� 100 �����, �������� ������ ���� �������� ����������,����� �� ��� �����������

void MainWindow::showEvent(){
    tray.showEvent();
}
