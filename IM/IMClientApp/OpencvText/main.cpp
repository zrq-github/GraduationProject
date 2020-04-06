#include "OpencvText.h"
#include <QtWidgets/QApplication>
#include<opencv2/opencv.hpp>
#include <QDebug>
#include <QDir>
using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //OpencvText w;
    //w.show();

    qDebug() << QDir::currentPath();
    qDebug() << QCoreApplication::applicationDirPath();

    return a.exec();
}
