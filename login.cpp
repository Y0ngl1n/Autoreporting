#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->passwordedit->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    if(ui->accountedit->text()==tr("admin")&&ui->passwordedit->text()==tr("123456")){
        accept();
    }
    else{
    QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);
    //如果不正确，弹出警告对话框
    }
}
