#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "singup.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle ("LOGIN");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/ANDISHE/Documents/grocery_store/grocery_db.db");
    if(!db.isOpen())
        db.open();



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_singupnow_clicked()
{
    SingUp *singup = new SingUp();
    singup->show();
    close();
}


void MainWindow::on_login_button_clicked()
{
    if(ui->username->text()=="" ||
            ui->password->text()=="")
    {
        QMessageBox::warning(this,"Field Empty","All fields are required");
    }
    else {
        QString username = ui->username->text();
        QString password = ui->password->text();

        QSqlQuery q;
        q.prepare("SELECT count(username) FROM users WHERE username== :username and password== :password");
        q.bindValue(":username",username);
        q.bindValue(":password", password);
        q.exec();
        if(q.first())
        {
            if(q.value(0).toString()=="0")
                QMessageBox::warning(this,"ERROR","Username or Password wrong");
            else
            {
                QMessageBox::information(this,"WELCOME","Welcome "+username);
                if (username=="Admin")
                {
                   Admin *admin= new Admin;
                   admin->show();
                   close();
                }
                else
                {
                    User *user = new User(nullptr,username);
                    user->show();
                    close();
                }
            }

        }

    }
}



