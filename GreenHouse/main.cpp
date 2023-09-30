#include "greenhouse.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GreenHouse w;
    w.show();
    return a.exec();
}
