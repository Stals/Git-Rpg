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
    //Тут мы читаем файл Stals.stats и храним в программе. ( после чего запустим func() чтобы убедиться не изменилось ли чего)


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
//прочитьать файл Stals и сравнить изменения с тем что щас есть,

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
