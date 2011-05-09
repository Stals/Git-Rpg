#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"
static User user;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //TODO: Может при отображении старых статов тоже делать это таймером, всмысле полоска едет и опыт заполняется, от нуля до того что щас( но не меняя уровень). После этого если есть файл Stals с изменениями, можно выдать сообщение в трей типо, о новые данные, щас я всё сделаю и начинает заполнять...
    //!!!Ну как минимум после включения если есть, то нужно давать сообщения о том что я вижу что есть новое( наверно это просто в func записать, чтобы он выдавать сообщение в трей каждый раз когда он начинает увеличивать на форме.)
    displayStats();
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
//прочитать файл Stals и сравнить изменения с тем что щас есть,

    //в таймере важно постоянно перерисовывать эелементы

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
