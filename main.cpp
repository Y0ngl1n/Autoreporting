#include "autoreporting.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    autoreporting w;
    w.setWindowTitle(QStringLiteral("激光自动报靶Demo(Version:20230317)"));
    w.show();

    return a.exec();
}
