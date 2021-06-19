#ifndef USERINFORMATION_H
#define USERINFORMATION_H

#include <QWidget>

namespace Ui {
class UserInformation;
}

class UserInformation : public QWidget
{
    Q_OBJECT

public:
    explicit UserInformation(QWidget *parent = nullptr);
    ~UserInformation();

private slots:
    void on_searchButton_clicked();

    void on_user_clicked(const QModelIndex &index);

private:
    Ui::UserInformation *ui;
};

#endif // USERINFORMATION_H
