#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include <fstream>

static User user;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //TODO: ����� ��� ����������� ������ ������ ���� ������ ��� ��������, ������� ������� ���� � ���� �����������, �� ���� �� ���� ��� ���( �� �� ����� �������). ����� ����� ���� ���� ���� Stals � �����������, ����� ������ ��������� � ���� ����, � ����� ������, ��� � �� ������ � �������� ���������...
    //!!!�� ��� ������� ����� ��������� ���� ����, �� ����� ������ ��������� � ��� ��� � ���� ��� ���� �����( ������� ��� ������ � func ��������, ����� �� �������� ��������� � ���� ������ ��� ����� �� �������� ����������� �� �����.)
    displayStats();
    //��� �� ������ ���� Stats.grpg � ������ � ���������. ( ����� ���� �������� func() ����� ��������� �� ���������� �� ����)


    //������ � ��� ��� ��� ����� ��������� �����, ����� ��������� �� ��������, ������� � ������ ���-�� ������� ������� ���.

        //��� ��� ����� ��������� ���������� , ��� ������ ����� ������ �����, � ����� ��� ��������� ��������� �� ����.������ ����� ��� ��������� ������ ��� ���� � �������� �� ���������� �� ��, �� ���� ��� �� �������� �� �������.

        //� ���� ��� ��� ��������, �� ��������� ����,���� ���.
        //��� ��� ���� ������ ��������� ���������� �� �����, � ����� ��� ���-�� ������ ���� ��
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::func(){
    ui->label->setText("ok");
    //���� ������� � ����� ������ ������ ����������
    std::pair<int,int> joint;//���� � ����� ���������� �� ����� Stals
    joint=changedExp();
    if(joint.first!=-1){//���� ���� ���������

        ui->userName->setText("Works");


  }


    //� ������� ����� ��������� �������������� ���������, ����� ������������ � ������� ����� ���������� ������ � ����� ��������� �������� ����� ��� ����� �� ��� ������ ������������. ( �������� ������� �� ���� ������� �������� ��������)

    //��������� ������� (������ ����������� �� ������ �� �����)
    //����� �������� levelup ���� ���������� ������ ������� ����� ��� ����� ������ ������ � ����������� ��� ����� � �� ������ ����.
    //�� ���� ���������� �� ����� ��� � ��������� ��������

    //+ ������ �������� ����� ��������� ��������� � ����, ��� ��� ����� ������ ������ ������� ���������� ��.
    //TODO ����� ����� ������� ������� ���� �������, ������� ����� ������� ������ � ������ ����� ���������� ���������  � ����
    //(����� �� �������� �� ������ N ������ ���� �� ��� � queue, � ����� ���� ���� ���-�� ����������)
}
void MainWindow::displayStats(){

    ui->userName->setText(user.name.c_str());

    //User
    ui->userLvl->setText("Joint Level "+QString::number(user.joint.lvl));
    ui->userExp->setText("[ "+QString::number(user.joint.exp)+" / "+QString::number(user.joint.maxExp)+" ]");
    ui->userBar->setValue(user.joint.exp);
    ui->userBar->setMaximum(user.joint.maxExp);
    //Plus
    ui->plusLvl->setText("Insertions (+) Level"+QString::number(user.plus.lvl));
    ui->plusExp->setText("[ "+QString::number(user.plus.exp)+" / "+QString::number(user.plus.maxExp)+" ]");
    ui->plusBar->setValue(user.plus.exp);
    ui->plusBar->setMaximum(user.plus.maxExp);
    //Minus
    ui->minusLvl->setText("Deleitions  (-) Level"+QString::number(user.minus.lvl));
    ui->minusExp->setText("[ "+QString::number(user.minus.exp)+" / "+QString::number(user.minus.maxExp)+" ]");
    ui->minusBar->setValue(user.minus.exp);
    ui->minusBar->setMaximum(user.minus.maxExp);
}
std::pair<int,int> MainWindow::changedExp(){
//������ ���� Stals � ���������� � ��� ��� ���� � User
//��� ����� ��� ����� ������� ��� ������ � ����� �� Stals
    int plus=0;
    int minus=0;
    int numberOfProjects;
    std::string projectName;
    int buf;

    std::ifstream f("Stals");

    f>>numberOfProjects;
    for(int i=0;i<numberOfProjects;++i){
        f>>projectName;
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
void MainWindow::on_pushButton_clicked()
{
    user.joint.exp+=1;
    user.plus.exp+=1;
    user.minus.exp+=1;
   displayStats();
}
