#include "editprofile.h"
#include "ui_editprofile.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

QString id;
EditProfile::EditProfile(QWidget *parent,QString username) :
    QWidget(parent),
    ui(new Ui::EditProfile)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/ANDISHE/Documents/grocery_store/grocery_db.db");
    if(!db.isOpen())
        db.open();
    QSqlQuery q;
    q.exec("SELECT * FROM users WHERE username='"+username+"'");
    if(q.first())
    {
        ui->username_s->setText(q.value(1).toString());
        ui->phonenumber_s->setText(q.value(4).toString());
        ui->password_s->setText(q.value(2).toString());
        ui->address_s->setText(q.value(3).toString());
        id=q.value(0).toString();

    }
}

EditProfile::~EditProfile()
{
    delete ui;
}

void EditProfile::on_update_button_clicked()
{
    if(ui->username_s->text()=="" ||
            ui->password_s->text()=="" ||
            ui->address_s->text()=="" ||
            ui->phonenumber_s->text()=="")
    {
        QMessageBox::warning(this,"Field Empty","All fields are required");
    }
    else {
        QString username = ui->username_s->text();
        QString password = ui->password_s->text();
        QString address = ui->address_s->text();
        QString phone= ui->phonenumber_s->text();

        QSqlQuery q;
        QString query_product = "UPDATE users SET username='"+username+"',password='"+password+"',address='"+address+"',phone='"+phone+"' WHERE id=="+id+"";
        if(q.exec(query_product))
            QMessageBox::information(this,"UPDATE","Profile update successfully");
        else
           QMessageBox::critical(this,"ERROR","This username exists");
    }
}

