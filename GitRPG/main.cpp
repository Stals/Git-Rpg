#include <QtGui/QApplication>
#include "mainwindow.h"


#include <QtCore>
#include <QtDebug>
#include <QObject>

class Watcher : public QFileSystemWatcher
{
        Q_OBJECT

public:
    MainWindow* _w;
        Watcher(MainWindow *w)
        {
            _w=w;

                addPath(QDir::current().filePath("main.cpp"));
                connect(this, SIGNAL(fileChanged(const QString&)), this, SLOT(fileChanged(const QString&)));
               // qDebug() << "monitoring" << files();

        }

private slots:
        void fileChanged(const QString& path)
        {
            _w->func();
               // qDebug() << "fileChanged" << path;
               // qDebug() << "-->" << files();
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

