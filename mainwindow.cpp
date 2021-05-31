#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringList>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_singupnow_clicked()
{
    singup = new SingUp();
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
        QFile user_file("users.txt");
        if(!user_file.open(QFile::ReadOnly| QFile::Text))
            QMessageBox::warning(this,"File Error","File not open");
        QString username = ui->username->text();
        QString password = ui->password->text();
        QTextStream in(&user_file);
        bool if_login=false;
        while(true)
        {
            QStringList user_pass = in.readLine().split(":");
            if(user_pass[0]==username && user_pass[1]==password)
            {
                QMessageBox::information(this,"Sing in Done","Welcome"+username);
                if (username=="Admin")
                {
                    user_file.close();
                    admin = new Admin();
                    admin->show();
                    close();
                    break;


                }


            }
        }
        if (!if_login)
        {
            QMessageBox::warning(this,"Invalid","Invalid username or password");
            ui->username->clear();
            ui->password->clear();
        }

    }
}

