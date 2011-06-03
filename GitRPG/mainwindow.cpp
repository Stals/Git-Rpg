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
    //TODO: ����� ��� ����������� ������ ������ ���� ������ ��� ��������, ������� ������� ���� � ���� �����������, �� ���� �� ���� ��� ���( �� �� ����� �������). ����� ����� ���� ���� ���� Stals � �����������, ����� ������ ��������� � ���� ����, � ����� ������, ��� � �� ������ � �������� ���������...
    //!!!�� ��� ������� ����� ��������� ���� ����, �� ����� ������ ��������� � ��� ��� � ���� ��� ���� �����( ������� ��� ������ � func ��������, ����� �� �������� ��������� � ���� ������ ��� ����� �� �������� ����������� �� �����.)

    progressBarTimer = new QTimer(this);
    connect(progressBarTimer, SIGNAL(timeout()),this,SLOT(increaseAll()));

    displayStats();

    setFixedSize(width(), height());//�� ��������� �������� ������ ����.

    connect(tray.minimizeAction,SIGNAL(triggered()),this,SLOT(hide()));//hides window if minimize in a tray menu was pressed
    connect(tray.maximizeAction,SIGNAL(triggered()),this,SLOT(show()));//shows window if maximize in a tray menu was pressed
    connect(tray.quitAction,SIGNAL(triggered()),this,SLOT(close()));//closes application if quit in a tray menu was pressed
    connect(tray.tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
	    this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));


    func();//��� ������ ����������� func() ����� ��������� ������ �� ��������� ���� ��������� ���� ��������� (����� ��� �������� ���� ���������� fileSystemWatchr)

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

	eQueue.push(notification,"Joint Level "+QString::number(user.joint.lvl).toStdString()+" ("+QString::number(user.joint.exp-user.joint.lastExp).toStdString()+"/"+QString::number(user.joint.maxExp-user.joint.lastExp).toStdString()+")\n"+
		    "Insertions Level "+QString::number(user.plus.lvl).toStdString()+" ("+QString::number(user.plus.exp-user.plus.lastExp).toStdString()+"/"+QString::number(user.plus.maxExp-user.plus.lastExp).toStdString()+")\n"+
		    "Delitions Level "+QString::number(user.minus.lvl).toStdString()+" ("+QString::number(user.minus.exp-user.minus.lastExp).toStdString()+"/"+QString::number(user.minus.maxExp-user.minus.lastExp).toStdString()+")");


	tray.showEvent();
	break;
    default:
	;
    }
}

void MainWindow::func(){
    ui->label->setText("ok");
    //���� ������� � ����� ������ ������ ����������



    if(getChangedExp()){//���� ���� ���������
	//! TODO: ����� ����� ������ �� ���������� Joint ����?
	eQueue.push(progress,"Insertions: "+QString::number(user.newExp.first-user.plus.exp).toStdString()+"\n"+
			     "Delitions: "+QString::number(user.newExp.second-user.minus.exp).toStdString());
	tray.showEvent();


        //����� �� ������ ���������� �������
        ui->label->setText("StartTimers");
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
            ++user.minus.exp;
            ui->minusBar->setValue(user.minus.exp);

        }

	user.checkForLvls();
	tray.showEvent();
	displayStats();
	Sleep(5);
    }
    user.saveStats();//����� ���� �������� ��������� �����
    progressBarTimer->stop();

}

//! ���� ���� � ������ ���������� � ����������� �� ���� ������� ��� �������� ��������
//! ��� ������ �� ������� ��� ������ ���� ������ ��� ������� ��������� � � ���� 4 ���� �����, ��� ������ ��� � � ���� 100 �����, �������� ������ ���� �������� ����������,����� �� ��� �����������
void MainWindow::on_pushButton_clicked()
{
    ++user.joint.exp;
    ++user.plus.exp;
    ++user.minus.exp;
    user.checkForLvls();
    displayStats();

    tray.showEvent();

}
