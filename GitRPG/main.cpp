#include <QtGui/QApplication>
#include "mainwindow.h"


#include <QtCore>
#include <QtDebug>
#include <QObject>
//Логика класса watcher заключается в том чтобы вызвать функцию func() , когда файл Stals будет изменен
class Watcher : public QFileSystemWatcher
{
    Q_OBJECT

public:
    MainWindow* _w;
    Watcher(MainWindow *w)
    {
	_w=w;

	addPath(QDir::current().filePath("Stals"));
	connect(this, SIGNAL(fileChanged(const QString&)), this, SLOT(fileChanged(const QString&)));

    }

private slots:
    void fileChanged(const QString& path)
    {
	_w->func();
    }
};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Watcher wa(&w);
    w.show();

    return a.exec();
}


#include "main.moc"

