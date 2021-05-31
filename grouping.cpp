#include "grouping.h"
#include "ui_grouping.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>

Grouping::Grouping(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Grouping)
{
    ui->setupUi(this);
    QFile groups_file("groups.txt");
    if(!groups_file.open(QFile::ReadOnly| QFile::Text))
        QMessageBox::warning(this,"File Error","File not open");
    QTextStream out(&groups_file);
    QString text = out.readAll();
    ui->existlist->setText(text);
    groups_file.close();
}

Grouping::~Grouping()
{
    delete ui;
}

void Grouping::on_add_clicked()
{
    QFile groups_file("groups.txt");
    if(!groups_file.open(QFile::Append| QFile::Text))
        QMessageBox::warning(this,"File Error","File not open");
    QTextStream in(&groups_file);
    in << ui->groupname->text()+"\n";
    QMessageBox::information(this,"Done","Group add");
    ui->groupname->clear();
    groups_file.close();

    if(!groups_file.open(QFile::ReadOnly| QFile::Text))
        QMessageBox::warning(this,"File Error","File not open");
    QTextStream out(&groups_file);
    QString text = out.readAll();
    ui->existlist->setText(text);
    groups_file.close();
}

