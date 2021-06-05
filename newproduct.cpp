#include "newproduct.h"
#include "ui_newproduct.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
NewProduct::NewProduct(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewProduct)
{
    ui->setupUi(this);
    QFile group_file("groups.txt");
    if(!group_file.open(QFile::ReadOnly| QFile::Text))
        QMessageBox::warning(this,"File Error","File not open");
    QTextStream out(&group_file);
    while(!out.atEnd())
    {
        ui->productgroup->addItem(out.readLine());
    }
    group_file.close();
}

NewProduct::~NewProduct()
{
    delete ui;
}
