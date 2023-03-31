#include "autoreporting.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login lgd;
    autoreporting w;
    lgd.setWindowTitle("登录");
    w.setWindowTitle(QStringLiteral("激光自动报靶Demo(Version:20230330)"));
    if(lgd.exec()==QDialog::Accepted){
    w.show();
    return a.exec();
    }
}
