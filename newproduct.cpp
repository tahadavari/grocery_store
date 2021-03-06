#include "newproduct.h"
#include "ui_newproduct.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
NewProduct::NewProduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewProduct)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/ANDISHE/Documents/grocery_store/grocery_db.db");
    if(!db.isOpen())
        db.open();

    QSqlQuery q;
    q.exec("SELECT name FROM groups");
    ui->productgroup->addItem("");
    while(q.next())
    {
        QString value=q.value(0).toString();
        ui->productgroup->addItem(value);
    }

}

NewProduct::~NewProduct()
{
    delete ui;
}

void NewProduct::on_add_clicked()
{
    if(ui->productname->text()=="" ||
            ui->productprice->text()=="" ||
            ui->productnumber->text()=="")
    {
        QMessageBox::warning(this,"Field Empty","All fields are required");
    }
    else {
        QSqlQuery q_groupid;
        QString productname = ui->productname->text();
        QString productbarnd = ui->productbrand->text();
        QString productprice = ui->productprice->text();
        QString productnumber = ui->productnumber->text();
        QString productgroup = ui->productgroup->currentText();
        q_groupid.exec("SELECT id FROM groups WHERE name=='"+productgroup+"'");
        QString productG;
        if(q_groupid.first())
            productG = q_groupid.value(0).toString();
        QSqlQuery q;
        QString query_product = "INSERT INTO products(name,brand,price,count,group_id) VALUES('"+productname+"','"+productbarnd+"',"+productprice+","+productnumber+","+productG+")";
        if(q.exec(query_product))
            QMessageBox::information(this,"DONE","Product added successfully");
        else
            QMessageBox::warning(this,"ERROR","This product exists");

        ui->productname->clear();
        ui->productbrand->clear();
        ui->productprice->clear();
        ui->productnumber->clear();
        ui->productgroup->setCurrentIndex(0);

    }
}





void NewProduct::on_reload_clicked()
{
    ui->productgroup->clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/ANDISHE/Documents/grocery_store/grocery_db.db");
    if(!db.isOpen())
        db.open();

    QSqlQuery q;
    q.exec("SELECT name FROM groups");
    ui->productgroup->addItem("");
    while(q.next())
    {
        QString value=q.value(0).toString();
        ui->productgroup->addItem(value);
    }
}

