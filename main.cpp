#include "mainscene.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    mainScene w;
    w.show();
    return application.exec();
}
