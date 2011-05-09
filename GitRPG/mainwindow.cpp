#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
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
//��������� ���� Stals � �������� ��������� � ��� ��� ��� ����,

    //� ������� ����� ��������� �������������� ���������

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
    ui->userLvl->setText("User Level "+QString::number(user.user.lvl));
    ui->userExp->setText("[ "+QString::number(user.user.exp)+" / "+QString::number(user.user.maxExp)+" ]");
    ui->userBar->setValue(user.user.exp);
    ui->userBar->setMaximum(user.user.maxExp);
    //Plus
    ui->plusLvl->setText("Plus Level "+QString::number(user.plus.lvl));
    ui->plusExp->setText("[ "+QString::number(user.plus.exp)+" / "+QString::number(user.plus.maxExp)+" ]");
    ui->plusBar->setValue(user.plus.exp);
    ui->plusBar->setMaximum(user.plus.maxExp);
    //Minus
    ui->minusLvl->setText("Minus Level "+QString::number(user.minus.lvl));
    ui->minusExp->setText("[ "+QString::number(user.minus.exp)+" / "+QString::number(user.minus.maxExp)+" ]");
    ui->minusBar->setValue(user.minus.exp);
    ui->minusBar->setMaximum(user.minus.maxExp);
}

void MainWindow::on_pushButton_clicked()
{
    user.user.exp+=1;
    user.plus.exp+=1;
    user.minus.exp+=1;
   displayStats();
}
