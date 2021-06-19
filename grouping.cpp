#include "grouping.h"
#include "ui_grouping.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

Grouping::Grouping(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Grouping)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/ANDISHE/Documents/grocery_store/grocery_db.db");
    if(!db.isOpen())
        db.open();
    QSqlQuery q;
    q.exec("SELECT name FROM groups");
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(q);
    ui->tableexisting->setModel(model);

}

Grouping::~Grouping()
{
    delete ui;
}

void Grouping::on_add_clicked()
{
    QString name=ui->groupname->text();
    QSqlQuery q;
    QString db_query = "INSERT INTO groups(name) VALUES('"+name+"')";
    if(q.exec(db_query))
        QMessageBox::information(this,"Done","Group add");
    else
        QMessageBox::warning(this,"ERROR","This group exists");
    ui->groupname->clear();
    q.exec("SELECT name FROM groups");
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(q);
    ui->tableexisting->setModel(model);

}

