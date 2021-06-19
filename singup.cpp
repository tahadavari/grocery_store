#include "singup.h"
#include "ui_singup.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include "user.h"
SingUp::SingUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SingUp)
{
    ui->setupUi(this);
    this->setWindowTitle ("SING UP");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/ANDISHE/Documents/grocery_store/grocery_db.db");
    if(!db.isOpen())
        db.open();
}

SingUp::~SingUp()
{
    delete ui;
}

void SingUp::on_Crate_button_clicked()
{
    QSqlQuery q;
    if(ui->address_s->text()=="" ||
            ui->phonenumber_s->text()=="" ||
            ui->username_s->text()=="" ||
            ui->password_s->text()=="")
    {
        QMessageBox::warning(this,"Field Empty","All fields are required");
    }

    else {


        QString username = ui->username_s->text();
        QString phone = ui->phonenumber_s->text();
        QString address = ui->address_s->text();
        QString password = ui->password_s->text();

        QString db_query = "INSERT INTO users(username,password,address,phone) VALUES('"+username+"','"+password+"','"+address+"','"+phone+"')";
        if(q.exec(db_query))
        {

            QMessageBox::StandardButton reply = QMessageBox::question(this,"Done","Your account was created successfully Do you want to log in to your account?");
            if(reply == QMessageBox::Yes)
            {
                User *user=new User(nullptr,username);
                user->show();
                close();
            }
            else
            {
                ui->username_s->clear();
                ui->phonenumber_s->clear();
                ui->address_s->clear();
                ui->password_s->clear();

            }
        }



        else
        {
            QMessageBox::critical(this,"ERROR","This username exists");
            ui->username_s->clear();
            ui->phonenumber_s->clear();
            ui->address_s->clear();
            ui->password_s->clear();
        }
    }

}



//void SingUp::on_pushButton_clicked()
//{

//    QSqlQueryModel *m=new QSqlQueryModel;
//    QSqlQuery q2;
//    q2.exec("SELECT * FROM users");
//    m->setQuery(q2);
//    ui->tableView->setModel(m);

//}


void SingUp::on_loginnow_clicked()
{
    MainWindow *login = new MainWindow();
    login->show();
    close();
}

