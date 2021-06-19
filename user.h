#ifndef USER_H
#define USER_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class User;
}

class User : public QDialog
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = nullptr,QString username="");
    ~User();

private slots:


    void on_group_activated(int index);

    void on_searchButton_clicked();

    void on_product_list_clicked(const QModelIndex &index);

    void on_available_stateChanged(int arg1);

    void on_available_clicked();

    void on_search_textChanged(const QString &arg1);

    void on_addtocart_clicked();


    void on_cart_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tabWidget_tabCloseRequested(int index);

    void on_product_list_cart_clicked(const QModelIndex &index);

    void on_deleteButton_clicked();

    void on_purchase_clicked();

    void on_editprofile_button_clicked();

    void on_exit_clicked();

private:
    Ui::User *ui;
};

#endif // USER_H
