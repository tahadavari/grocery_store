#include "deleteproduct.h"
#include "ui_deleteproduct.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

DeleteProduct::DeleteProduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteProduct)
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
}

DeleteProduct::~DeleteProduct()
{
    delete ui;
}

void DeleteProduct::on_delete_2_clicked()
{
    QSqlQuery q;
    if(ui->products->currentText()=="")
        QMessageBox::warning(this,"DELETE","Unselected products to delete");
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"DELETE","Are you sure you want to delete this product??");
        if(reply == QMessageBox::Yes)
        {
            QString del_product=ui->products->currentText();

            if(q.exec("DELETE FROM products WHERE name=='"+del_product+"'"))
                QMessageBox::information(this,"DELETE","Deletion completed successfully");
        }
        ui->products->clear();
        q.exec("SELECT name FROM products");
        ui->products->addItem("");
        while(q.next())
        {
            QString value=q.value(0).toString();
            ui->products->addItem(value);
        }
    }

}

