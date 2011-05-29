#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include "eventqueue.h"
#include <fstream>
#include <windows.h>
#include "tray.h"



std::pair<int,int>newExp;//���� � ����� ���������� �� ����� Stals
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
    Tray tray;

   func();//��� ������ ����������� func() ����� ��������� ������ �� ��������� ���� ��������� ���� ��������� (����� ��� �������� ���� ���������� fileSystemWatchr)
 }

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::func(){
    ui->label->setText("ok");
    //���� ������� � ����� ������ ������ ����������

   newExp=changedExp();

    if(newExp.first!=-1){//���� ���� ���������
        //! TODO: ���� ��������� � ���� ��� ��������� ����� ������ � ��� � �� ������.
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
//_________________________________
//eventqueue test
//eQueue.push(levelUp,"message");
   if(eQueue.empty()==false){
        eventPair pair=eQueue.pop();
        ui->label->setText(pair.message.c_str());
}
//if(eQueue.empty()==true){ ui->label->setText("������");}
}
std::pair<int,int> MainWindow::changedExp(){
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
    std::pair<int,int> joint;


    if((plus>user.plus.exp)||(minus>user.minus.exp)){
        joint.first=plus;
        joint.second=minus;

        return joint;
    }else{
        joint.first=-1;
        joint.second=-1;

        return joint;
    }

}

void MainWindow::increaseAll(){

    while((user.plus.exp<newExp.first)||(user.minus.exp<newExp.second)||(user.joint.exp<(newExp.first+newExp.second))){
        if(user.joint.exp<(newExp.first+newExp.second)){
            ++user.joint.exp;
            ui->jointBar->setValue(user.joint.exp);
        }
        if(user.plus.exp<newExp.first){
            ++user.plus.exp;
            ui->plusBar->setValue(user.plus.exp);
        }
        if(user.minus.exp<newExp.second){
            ++user.minus.exp;
            ui->minusBar->setValue(user.minus.exp);

        }

    user.checkForLvls();
    displayStats();
    Sleep(5);
    }
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



}
