#include "editproduct.h"
#include "ui_editproduct.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

EditProduct::EditProduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditProduct)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/ANDISHE/Documents/grocery_store/grocery_db.db");
    if(!db.isOpen())
        db.open();
    QSqlQuery q;
    q.exec("SELECT name FROM products");
    ui->products->addItem("");
    while(q.next())
    {
        QString value=q.value(0).toString();
        ui->products->addItem(value);
    }
    q.exec("SELECT name FROM groups");
    ui->productgroup->addItem("");
    while(q.next())
    {
        QString value=q.value(0).toString();
        ui->productgroup->addItem(value);
    }
}

EditProduct::~EditProduct()
{
    delete ui;
}


void EditProduct::on_products_activated(int index)
{
    QString edit_product=ui->products->currentText();
    QSqlQuery q;
    q.exec("SELECT * FROM products WHERE name=='"+edit_product+"'");
    if(ui->products->currentText()=="")
    {
        ui->productname->clear();
        ui->productbrand->clear();
        ui->productprice->clear();
        ui->productnumber->clear();
        ui->productgroup->setCurrentIndex(0);

    }

    if(q.first())
    {
        ui->productname->setText(q.value(1).toString());
        ui->productbrand->setText(q.value(2).toString());
        ui->productprice->setText(q.value(3).toString());
        ui->productnumber->setText(q.value(4).toString());
        ui->productgroup->setCurrentIndex(q.value(5).toInt());

    }
}


void EditProduct::on_update_clicked()
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
        QString query_product = "UPDATE products SET brand='"+productbarnd+"',price="+productprice+",count="+productnumber+",group_id="+productG+" WHERE name=='"+productname+"'";
        if(q.exec(query_product))
            QMessageBox::information(this,"UPDATE","Product update successfully");

        ui->products->setCurrentIndex(0);
        ui->productname->clear();
        ui->productbrand->clear();
        ui->productprice->clear();
        ui->productnumber->clear();
        ui->productgroup->setCurrentIndex(0);

    }
}

