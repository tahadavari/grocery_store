#include "singup.h"
#include "ui_singup.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
SingUp::SingUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingUp)
{
    ui->setupUi(this);
}

SingUp::~SingUp()
{
    delete ui;
}

void SingUp::on_Crate_button_clicked()
{
    if(ui->address_s->text()=="" ||
            ui->phonenumber_s->text()=="" ||
            ui->username_s->text()=="" ||
            ui->password_s->text()=="")
    {
        QMessageBox::warning(this,"Field Empty","All fields are required");
    }
    else {
        QFile user_file("users.txt");
        if(!user_file.open(QFile::Append| QFile::Text))
            QMessageBox::warning(this,"File Error","File not open");
        QTextStream out(&user_file);
        QString username = ui->username_s->text();
        QString phonenumber = ui->phonenumber_s->text();
        QString address = ui->address_s->text();
        QString password = ui->password_s->text();
        out << username+":"+password+":"+phonenumber+":"+address+"\n";
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Done","Your account was created successfully Do you want to log in to your account?");
        if(reply == QMessageBox::Yes)
        {
            QMessageBox::warning(this,"davkm","in profile now");
        }
        else
        {
            ui->username_s->clear();
            ui->phonenumber_s->clear();
            ui->address_s->clear();
            ui->password_s->clear();
            user_file.close();
        }

    }
}

