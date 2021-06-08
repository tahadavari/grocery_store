#ifndef SINGUP_H
#define SINGUP_H

#include <QDialog>
#include "user.h"
#include "mainwindow.h"
namespace Ui {
class SingUp;
}

class SingUp : public QDialog
{
    Q_OBJECT

public:
    explicit SingUp(QWidget *parent = nullptr);
    ~SingUp();

private slots:
    void on_Crate_button_clicked();

//    void on_pushButton_clicked();

    void on_loginnow_clicked();

private:
    Ui::SingUp *ui;
};

#endif // SINGUP_H
