#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
#include <fstream>
#include <windows.h>
std::pair<int,int>newExp;//плюс и минус полученные из файла Stals
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
   func();

    //Тут мы читаем файл Stats.grpg и храним в программе. ( после чего запустим func() чтобы убедиться не изменилось ли чего)


    //прикол в том что гит может увеличить число, когда программа не работает, поэтому я должен где-то хранить текущий лвл.

        //Так что когда программа включается , она должна брать оттуда статы, а потом уже проверять изменился ли файл.Тоесть сразу при включении читать тот файл и смотреть не отличается ли он, от того что он прочитал из другого.

        //А если она уже работает, то вызовется функ,если что.
        //Так что функ должен проверять изменились ли числа, а потом уже что-то делать если да
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::func(){
    ui->label->setText("ok");
    //Если измения в опыте влияют начать увеличение

   newExp=changedExp();

    if(newExp.first!=-1){//если были изменения
        //TODO: дать сообщение в трей что появились новые данные и щас я всё сделаю.
        //тогда мы должны стартовать таймеры
        ui->label->setText("StartTimers");
    progressBarTimer->start(1);

  }


    //в таймере важно постоянно перерисовывать эелементы, также теоритически в таймере можно стартовать быстро а потом замедлять скорость чтобы под конец не так быстро прибавлялось. ( скорость зависит от того сколько осталось дабавить)

    //запустить таймеры (начать увеличивать со старых до новых)
    //когда делается levelup этим занимается другая функция чтобы она могла давать ачивки и расчитывать всю экспе и тп внутри себя.
    //Но само увеличение по чутку идёт в отдельных таймерах

    //+ внутри таймеров могут появиться сообщения в трей, так что нужно начать таймер который отображает их.
    //TODO может можно сделать эксепшн типа события, которое может поймать таймер и только тогда показывать сообщения  в трей
    //(чтобы он проверял не каждые N секунд есть ли что в queue, а делал если туда что-то добавилось)
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
    std::pair<int,int> joint;


    if((plus>user.plus.exp)||(minus>user.minus.exp)){
        joint.first=plus;
        joint.second=minus;
      //  ui->label->setText("tyt1");
        return joint;
    }else{
        ui->label->setText(QString::number(plus)+" "+QString::number(minus));
        joint.first=-1;
        joint.second=-1;
       // ui->label->setText("tyt2");
        return joint;
    }

}

void MainWindow::increaseAll(){

    while((user.plus.exp<newExp.first)||(user.minus.exp<newExp.second)){//||(user.joint.exp<(newExp.first+newExp.second))){
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
    Sleep(100);
    }
}
//TODOполучается еще нужен стат minimumExp это опыт который был нужнен на прошлый уровень, вначале он =0, и используется для того чтобы вычитать из текущего опыта минимальный, и это и будет value для progressbara , также вычитаем его из maximumExp и это ставим как maximumValue
void MainWindow::on_pushButton_clicked()
{
   ++user.joint.exp;
   ++user.plus.exp;
   ++user.minus.exp;
   user.checkForLvls();
   displayStats();
}
