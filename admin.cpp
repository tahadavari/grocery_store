#include "admin.h"
#include "ui_admin.h"
#include "mainwindow.h"
#include "grouping.h"
#include "newproduct.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>





Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    this->setWindowTitle ("ADMIN PANNEL");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/ANDISHE/Documents/grocery_store/grocery_db.db");
    if(!db.isOpen())
        db.open();
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_editproduct_button_clicked()
{
    ui->tabWidget->addTab(new QWidget,"Edit Product");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    ui->tabWidget->setTabIcon(ui->tabWidget->currentIndex(),QIcon("D:/grocery_store/grocery_store/assets/icons/edit.png"));
}


void Admin::on_tabWidget_tabCloseRequested(int index)
{
    if(index>0)
        ui->tabWidget->removeTab(index);
}


void Admin::on_newproduct_button_clicked()
{
    ui->tabWidget->addTab(new NewProduct,"New Product");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    ui->tabWidget->setTabIcon(ui->tabWidget->currentIndex(),QIcon("D:/grocery_store/grocery_store/assets/icons/plus.png"));
}



void Admin::on_deleteproduct_button_clicked()
{
    ui->tabWidget->addTab(new QWidget,"Delete Product");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    ui->tabWidget->setTabIcon(ui->tabWidget->currentIndex(),QIcon("D:/grocery_store/grocery_store/assets/icons/trash.png"));
}



void Admin::on_grouping_button_clicked()
{
    ui->tabWidget->addTab(new Grouping,"Grouping");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    ui->tabWidget->setTabIcon(ui->tabWidget->currentIndex(),QIcon("D:/grocery_store/grocery_store/assets/icons/competition.png"));
}


void Admin::on_userinformation_button_clicked()
{
    ui->tabWidget->addTab(new QWidget,"User Information");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    ui->tabWidget->setTabIcon(ui->tabWidget->currentIndex(),QIcon("D:/grocery_store/grocery_store/assets/icons/information (1).png"));

}


void Admin::on_logout_button_clicked()
{
      MainWindow *login = new MainWindow();
      login->show();
      close();

}



