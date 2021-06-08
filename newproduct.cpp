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
            ui->productbrand->text()=="" ||
            ui->productprice->text()=="" ||
            ui->productnumber->text()=="")
    {
        QMessageBox::warning(this,"Field Empty","All fields are required");
    }
    else {
        QFile product_file("products.txt");
        if(!product_file.open(QFile::Append| QFile::Text))
            QMessageBox::warning(this,"File Error","File not open");
        QTextStream out(&product_file);
        QString productname = ui->productname->text();
        QString productbarnd = ui->productbrand->text();
        QString productprice = ui->productprice->text();
        QString productnumber = ui->productnumber->text();
        QString productgroup = ui->productgroup->currentText();
        out << productname+":"+productbarnd+":"+productprice+":"+productgroup+":"+productnumber+"\n";
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Done","Your account was created successfully Do you want to log in to your account?");
        if(reply == QMessageBox::Yes)
        {
            QMessageBox::warning(this,"davkm","in profile now");
        }
        else
        {

        }

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
    while(q.next())
    {
        QString value=q.value(0).toString();
        ui->productgroup->addItem(value);
    }
}

