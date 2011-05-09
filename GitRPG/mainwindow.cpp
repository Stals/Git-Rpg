#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
static User user;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    displayStats();
    //��� �� ������ ���� Stals.stats � ������ � ���������. ( ����� ���� �������� func() ����� ��������� �� ���������� �� ����)


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
//���������� ���� Stals � �������� ��������� � ��� ��� ��� ����,

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
    ui->userLvl->setText("User Level "+QString::number(user.userLvl));
    ui->userExp->setText("[ "+QString::number(user.userExp)+" / "+QString::number(user.userMaxExp)+" ]");
    ui->userBar->setValue(user.userExp);
    ui->userBar->setMaximum(user.userMaxExp);
    //Plus
    ui->plusLvl->setText("Plus Level "+QString::number(user.plusLvl));
    ui->plusExp->setText("[ "+QString::number(user.plusExp)+" / "+QString::number(user.plusMaxExp)+" ]");
    ui->plusBar->setValue(user.plusExp);
    ui->plusBar->setMaximum(user.plusMaxExp);
    //Minus
    ui->minusLvl->setText("Minus Level "+QString::number(user.minusLvl));
    ui->minusExp->setText("[ "+QString::number(user.minusExp)+" / "+QString::number(user.minusMaxExp)+" ]");
    ui->minusBar->setValue(user.minusExp);
    ui->minusBar->setMaximum(user.minusMaxExp);
}
