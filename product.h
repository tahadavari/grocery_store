#ifndef PRODUCT_H
#define PRODUCT_H

#include <QWidget>

namespace Ui {
class Product;
}

class Product : public QWidget
{
    Q_OBJECT

public:
    explicit Product(QWidget *parent = nullptr);
    ~Product();

private:
    Ui::Product *ui;
};

#endif // PRODUCT_H
