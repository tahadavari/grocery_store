#include "userinformation.h"
#include "ui_userinformation.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>


UserInformation::UserInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInformation)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/ANDISHE/Documents/grocery_store/grocery_db.db");
    if(!db.isOpen())
        db.open();
    QSqlQuery q;
    q.exec("SELECT username FROM users WHERE not username=='Admin'");
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(q);
    ui->user->setModel(model);

    ui->search_by->addItem("username");
    ui->search_by->addItem("phone number");
    ui->search_by->addItem("address");
}

UserInformation::~UserInformation()
{
    delete ui;
}

void UserInformation::on_searchButton_clicked()
{
    QSqlQuery q;

    QString search_key = ui->search->text();
    search_key=search_key.toLower();
    if(search_key!="")
    {
        QString query;
        if(ui->search_by->currentText()=="username")
            query = "SELECT username FROM users WHERE lower(username) like '%"+search_key+"%' AND NOT username='Admin'";
        else if(ui->search_by->currentText()=="phone number")
            query = "SELECT username FROM users WHERE phone like '%"+search_key+"%' AND NOT username='Admin'";
        else if(ui->search_by->currentText()=="address")
            query = "SELECT username FROM users WHERE lower(address) like '%"+search_key+"%' AND NOT username='Admin'";
        q.exec(query);
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(q);
        ui->user->setModel(model);

    }
}


void UserInformation::on_user_clicked(const QModelIndex &index)
{
    QString username = ui->user->currentIndex().data().toString();
    QSqlQuery q;
    q.exec("SELECT username,phone,address FROM users WHERE username='"+username+"'");
    if(q.first())
    {
        ui->username->setText(q.value(0).toString());
        ui->phone->setText(q.value(1).toString());
        ui->address->setText(q.value(2).toString());
    }
}

