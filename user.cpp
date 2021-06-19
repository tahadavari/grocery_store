#include "user.h"
#include "ui_user.h"
#include "product.h"
#include "editprofile.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>


User::User(QWidget *parent,QString username) :
    QDialog(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);
    ui->username_label->setText(username);
    ui->tabWidget->removeTab(1);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/ANDISHE/Documents/grocery_store/grocery_db.db");
    if(!db.isOpen())
        db.open();
    QSqlQuery q;
    q.exec("SELECT name FROM products");
    QSqlQueryModel *model=new QSqlQueryModel;
    model->setQuery(q);
    ui->product_list->setModel(model);

    q.exec("SELECT name FROM groups");
    ui->group->addItem("");
    while(q.next())
    {
        QString value=q.value(0).toString();
        ui->group->addItem(value);
    }



    q.exec("CREATE TABLE '"+username+"' ('price'	INTEGER,'name'	TEXT,'count'	INTEGER);");

    q.exec("SELECT count(name) FROM '"+username+"' ");
    if(q.first())
        ui->cart_count->setText(q.value(0).toString());


}

User::~User()
{
    QSqlQuery q;
    delete ui;
}

void User::on_group_activated(int index)
{
    if(ui->available->isChecked()){
        QString group_name=ui->group->currentText();
        if(group_name=="")
        {
            QSqlQuery q;
            q.exec("SELECT name FROM products WHERE count>0 ");
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);
        }
        else
        {
            QSqlQuery q;
            QString id;
            q.exec("SELECT id FROM groups WHERE name=='"+group_name+"'");
            if(q.first())
                id = q.value(0).toString();
            q.exec("SELECT name FROM products WHERE group_id=="+id+" AND count>0");
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);
        }}
    if(!ui->available->isChecked()){
        QString group_name=ui->group->currentText();
        if(group_name=="")
        {
            QSqlQuery q;
            q.exec("SELECT name FROM products");
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);
        }
        else
        {
            QSqlQuery q;
            QString id;
            q.exec("SELECT id FROM groups WHERE name=='"+group_name+"'");
            if(q.first())
                id = q.value(0).toString();
            q.exec("SELECT name FROM products WHERE group_id=="+id+"");
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);
        }}
}


void User::on_searchButton_clicked()
{
    if(!ui->available->isChecked()){
        QSqlQuery q;
        QString query;
        QString group_name=ui->group->currentText();
        QString search_key = ui->search->text();
        search_key=search_key.toLower();
        if(search_key!="")
        {
            if(group_name=="")
            {
                query = "SELECT name FROM products WHERE lower(name) like '%"+search_key+"%'";
            }
            else
            {
                QString id;
                q.exec("SELECT id FROM groups WHERE name=='"+group_name+"'");
                if(q.first())
                    id = q.value(0).toString();
                query = "SELECT name FROM products WHERE lower(name) like '%"+search_key+"%' AND group_id=="+id+"";
            }
            q.exec(query);
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);


        }}

    if(ui->available->isChecked()){
        QSqlQuery q;
        QString query;
        QString group_name=ui->group->currentText();
        QString search_key = ui->search->text();
        search_key=search_key.toLower();
        if(search_key!="")
        {
            if(group_name=="")
            {
                query = "SELECT name FROM products WHERE lower(name) like '%"+search_key+"%' AND count>0";
            }
            else
            {
                QString id;
                q.exec("SELECT id FROM groups WHERE name=='"+group_name+"'");
                if(q.first())
                    id = q.value(0).toString();
                query = "SELECT name FROM products WHERE lower(name) like '%"+search_key+"%' AND group_id=="+id+" AND count>0";
            }
            q.exec(query);
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);


        }}

}


void User::on_product_list_clicked(const QModelIndex &index)
{
    QString productname = ui->product_list->currentIndex().data().toString();
    QSqlQuery q;
    QSqlQuery q2;
    q2.exec("SELECT count(name) FROM "+ui->username_label->text()+" WHERE name='"+productname+"'");
    q.exec("SELECT name,price,count FROM products WHERE name='"+productname+"'");
    if(q.first() && q2.first())
    {
        ui->productname->setText(q.value(0).toString());
        if(q.value(2).toUInt()<1)
        {
            ui->count->setEnabled(false);
            ui->count->repaint();
            ui->count->setStyleSheet("#count{background:gray;border-radius:25px;color:#d9faff;}");
            ui->frame_11->setStyleSheet("#frame_11{background:gray;border-radius:25px;color:#00204a;}");
            ui->addtocart->setEnabled(false);
            ui->addtocart->repaint();
            ui->addtocart->setStyleSheet("background:gray;border-radius:25px;color:#d9faff;");
            ui->price->setStyleSheet("color:red;");
            ui->price->setText("not available");
            ui->addtocart->setText("not available");
        }
        else if (q2.value(0).toInt()>0)
        {
            ui->count->setEnabled(false);
            ui->count->repaint();
            ui->count->setStyleSheet("#count{background:gray;border-radius:25px;color:#d9faff;}");
            ui->frame_11->setStyleSheet("#frame_11{background:gray;border-radius:25px;color:#00204a;}");
            ui->addtocart->setEnabled(false);
            ui->addtocart->repaint();
            ui->addtocart->setStyleSheet("background:green;border-radius:25px;color:#d9faff;");
            ui->addtocart->setText("In your cart");
        }
        else
        {
            ui->count->setEnabled(true);
            ui->count->repaint();
            ui->count->setStyleSheet("#count{background:#00BBF0;border-radius:25px;color:#00204a;}");
            ui->frame_11->setStyleSheet("#frame_11{background:#00BBF0;border-radius:25px;color:#00204a;}");
            ui->addtocart->setEnabled(true);
            ui->addtocart->repaint();
            ui->addtocart->setStyleSheet("#addtocart{background:#005792;border-radius:25px;color:#d9faff;}#addtocart:hover{background:#00204a;border-radius:25px;color:#d9faff;}");
            ui->price->setStyleSheet("color:#005792;");
            ui->price->setText(q.value(1).toString());
            ui->addtocart->setText("Add to cart");
        }
    }
}


void User::on_available_stateChanged(int arg1)
{
    if(ui->available->isChecked())
    {
        QString group_name=ui->group->currentText();
        if(group_name=="")
        {
            QSqlQuery q;
            q.exec("SELECT name FROM products WHERE count>0 ");
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);
        }
        else
        {
            QSqlQuery q;
            QString id;
            q.exec("SELECT id FROM groups WHERE name=='"+group_name+"'");
            if(q.first())
                id = q.value(0).toString();
            q.exec("SELECT name FROM products WHERE group_id=="+id+" AND count>0");
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);
        }}
    if(!ui->available->isChecked()){
        QString group_name=ui->group->currentText();
        if(group_name=="")
        {
            QSqlQuery q;
            q.exec("SELECT name FROM products");
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);
        }
        else
        {
            QSqlQuery q;
            QString id;
            q.exec("SELECT id FROM groups WHERE name=='"+group_name+"'");
            if(q.first())
                id = q.value(0).toString();
            q.exec("SELECT name FROM products WHERE group_id=="+id+"");
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);
        }
    }
}


void User::on_available_clicked()
{
    if(ui->available->isChecked())
    {
        QString group_name=ui->group->currentText();
        if(group_name=="")
        {
            QSqlQuery q;
            q.exec("SELECT name FROM products WHERE count>0 ");
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);
        }
        else
        {
            QSqlQuery q;
            QString id;
            q.exec("SELECT id FROM groups WHERE name=='"+group_name+"'");
            if(q.first())
                id = q.value(0).toString();
            q.exec("SELECT name FROM products WHERE group_id=="+id+" AND count>0");
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);
        }}
    if(!ui->available->isChecked()){
        QString group_name=ui->group->currentText();
        if(group_name=="")
        {
            QSqlQuery q;
            q.exec("SELECT name FROM products");
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);
        }
        else
        {
            QSqlQuery q;
            QString id;
            q.exec("SELECT id FROM groups WHERE name=='"+group_name+"'");
            if(q.first())
                id = q.value(0).toString();
            q.exec("SELECT name FROM products WHERE group_id=="+id+"");
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);
        }
    }
}


void User::on_search_textChanged(const QString &arg1)
{
    if(!ui->available->isChecked()){
        QSqlQuery q;
        QString query;
        QString group_name=ui->group->currentText();
        QString search_key = ui->search->text();
        search_key=search_key.toLower();
        if(search_key!="")
        {
            if(group_name=="")
            {
                query = "SELECT name FROM products WHERE lower(name) like '%"+search_key+"%'";
            }
            else
            {
                QString id;
                q.exec("SELECT id FROM groups WHERE name=='"+group_name+"'");
                if(q.first())
                    id = q.value(0).toString();
                query = "SELECT name FROM products WHERE lower(name) like '%"+search_key+"%' AND group_id=="+id+"";
            }
            q.exec(query);
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);


        }
        else if(search_key=="")
        {
            if(group_name=="")
            {
                query = "SELECT name FROM products ";
            }
            else
            {
                QString id;
                q.exec("SELECT id FROM groups WHERE name=='"+group_name+"'");
                if(q.first())
                    id = q.value(0).toString();
                query = "SELECT name FROM products WHERE group_id=="+id+"";
            }
            q.exec(query);
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);


        }
    }

    if(ui->available->isChecked()){
        QSqlQuery q;
        QString query;
        QString group_name=ui->group->currentText();
        QString search_key = ui->search->text();
        search_key=search_key.toLower();
        if(search_key!="")
        {
            if(group_name=="")
            {
                query = "SELECT name FROM products WHERE lower(name) like '%"+search_key+"%' AND count>0";
            }
            else
            {
                QString id;
                q.exec("SELECT id FROM groups WHERE name=='"+group_name+"'");
                if(q.first())
                    id = q.value(0).toString();
                query = "SELECT name FROM products WHERE lower(name) like '%"+search_key+"%' AND group_id=="+id+" AND count>0";
            }
            q.exec(query);
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);


        }
        else if(search_key=="")
        {
            if(group_name=="")
            {
                query = "SELECT name FROM products WHERE count>0 ";
            }
            else
            {
                QString id;
                q.exec("SELECT id FROM groups WHERE name=='"+group_name+"' AND count>0");
                if(q.first())
                    id = q.value(0).toString();
                query = "SELECT name FROM products WHERE group_id=="+id+" AND count>0";
            }
            q.exec(query);
            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery(q);
            ui->product_list->setModel(model);


        }}
}


void User::on_addtocart_clicked()
{
    if(ui->productname->text()=="")
        QMessageBox::warning(this,"ADD","Product not selected for add");
    else
    {
        QString username = ui->username_label->text();
        QSqlQuery q;
        int count;
        int countbox = ui->count->value();
        QString name=ui->productname->text();
        QString price=ui->price->text();
        q.exec("SELECT count FROM products WHERE name=='"+name+"'");
        if(q.first())
            count = q.value(0).toInt();
        if (count>=countbox)
        {
            QMessageBox::information(this,"DONE","Product added to your cart");
            q.exec("INSERT INTO "+username+"(name,price,count) VALUES('"+name+"',"+price+","+QString::number(countbox)+")");
            ui->cart_count->setText(QString::number(ui->cart_count->text().toInt()+1));
            ui->productname->setText("");
            ui->price->setText("");
        }
        else
        {
            QMessageBox::critical(this,"ERROR","The number of inputs is more than the available number");
        }
    }
}


void User::on_cart_clicked()
{
    ui->tabWidget->addTab(ui->tab,"Cart");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}


void User::on_tabWidget_currentChanged(int index)
{
    QSqlQuery q;
    q.exec("SELECT sum(count*price) FROM "+ui->username_label->text()+"");
    if(q.first())
        ui->pricesum->setText(q.value(0).toString());
    if(index==1)
    {
        ui->cart->setEnabled(false);
        q.exec("SELECT name,count,price FROM "+ui->username_label->text()+"");
        QSqlQueryModel *model=new QSqlQueryModel;
        model->setQuery(q);
        ui->product_list_cart->setModel(model);
    }
    else if(index==0)
    {
        ui->cart->setEnabled(true);
    }
}


void User::on_tabWidget_tabCloseRequested(int index)
{
    if(index!=0)
        ui->tabWidget->removeTab(index);
}


void User::on_product_list_cart_clicked(const QModelIndex &index)
{
    QString click = ui->product_list_cart->currentIndex().data().toString();
    QSqlQuery q;
    q.exec("SELECT name,price,count FROM "+ui->username_label->text()+" WHERE name='"+click+"' or price='"+click+"' or count='"+click+"'" );
    if(q.first())
    {
        ui->delete_product->setText(q.value(0).toString());
    }
}


void User::on_deleteButton_clicked()
{
    if(ui->delete_product->text()=="")
        QMessageBox::warning(this,"DELETE","Product not selected for deletion");
    else
    {
        QSqlQuery q;
        QString del_product=ui->delete_product->text();
        QMessageBox::StandardButton reply = QMessageBox::question(this,"DELETE","Are you sure you want to delete "+del_product+"?");
        if(reply == QMessageBox::Yes)
        {
            if(q.exec("DELETE FROM "+ui->username_label->text()+" WHERE name=='"+del_product+"'"))
                QMessageBox::information(this,"DELETE","Deletion completed successfully");
            ui->cart_count->setText(QString::number(ui->cart_count->text().toInt()-1));
        }
        ui->delete_product->clear();

        q.exec("SELECT name,count,price FROM "+ui->username_label->text()+"");
        QSqlQueryModel *model=new QSqlQueryModel;
        model->setQuery(q);
        ui->product_list_cart->setModel(model);
    }
}


void User::on_purchase_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Purchase","You are sure of your purchase?");
    if(reply == QMessageBox::Yes)
    {
        QMessageBox::information(this,"Purchase","Your purchase was completed successfully");
        ui->cart_count->setText("0");
        ui->pricesum->setText("");

        QSqlQuery q;
        QSqlQuery q2;
        q.exec("SELECT name,count FROM "+ui->username_label->text()+"");
        while(q.next())
        {
            q2.exec("UPDATE products SET count=count-"+q.value(1).toString()+" WHERE name=='"+q.value(0).toString()+"'");
        }
        q.exec("DELETE FROM "+ui->username_label->text()+"");
        q.exec("SELECT name,count,price FROM "+ui->username_label->text()+"");
        QSqlQueryModel *model=new QSqlQueryModel;
        model->setQuery(q);
        ui->product_list_cart->setModel(model);
    }
}


void User::on_editprofile_button_clicked()
{
    ui->tabWidget->addTab(new EditProfile(nullptr,ui->username_label->text()),"Edit Profile");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
}


void User::on_exit_clicked()
{
    MainWindow *login = new MainWindow();
    login->show();
    close();
}

