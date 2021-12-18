#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    if(ui->nameLine->text().trimmed() == tr("tom") && ui->nameLine_2->text().trimmed() == tr("password"))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, tr("warning"), tr("username or password error!"), QMessageBox::Yes);
       //clear the editline
        ui->nameLine->clear();
        ui->nameLine_2->clear();
        //locate the mouse
        ui->nameLine->setFocus();
    }
}
