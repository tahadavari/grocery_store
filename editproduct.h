#ifndef EDITPRODUCT_H
#define EDITPRODUCT_H

#include <QWidget>

namespace Ui {
class EditProduct;
}

class EditProduct : public QWidget
{
    Q_OBJECT

public:
    explicit EditProduct(QWidget *parent = nullptr);
    ~EditProduct();

private slots:

    void on_products_activated(int index);

    void on_update_clicked();

private:
    Ui::EditProduct *ui;
};

#endif // EDITPRODUCT_H
