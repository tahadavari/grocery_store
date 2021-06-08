#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>


namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private slots:
    void on_editproduct_button_clicked();

    void on_tabWidget_tabCloseRequested(int index);

    void on_newproduct_button_clicked();

    void on_deleteproduct_button_clicked();

    void on_grouping_button_clicked();

    void on_userinformation_button_clicked();

    void on_logout_button_clicked();

    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
