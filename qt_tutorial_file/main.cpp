#include <QCoreApplication>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>

void write(QString filename)
{
    QFile mfile(filename);
    if(!mfile.open(QFile::WriteOnly | QFile::Text) )
    {
        qDebug() << "file cannot open for writing";
        return;
    }

    QTextStream out(&mfile);
    QString mText = out.readAll();
    out << "hello world";
    qDebug() << mText;
    mfile.flush();
    mfile.close();

}

void read(QString filename)
{
    QFile mfile(filename);
    if(!mfile.open(QFile::ReadOnly | QFile::Text) )
    {
        qDebug() << "file cannot open for reading";
        return;
    }
    else
    {
        QTextStream in(&mfile);
        QString mText = in.readAll();
        qDebug() << mText;
        mfile.close();
    }
}




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filename = "/home/grdl/qt_projects/test.txt";
    write(filename);
    read(filename);


    return a.exec();
}
