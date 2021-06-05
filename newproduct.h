#ifndef NEWPRODUCT_H
#define NEWPRODUCT_H

#include <QWidget>

namespace Ui {
class NewProduct;
}

class NewProduct : public QWidget
{
    Q_OBJECT

public:
    explicit NewProduct(QWidget *parent = nullptr);
    ~NewProduct();

private:
    Ui::NewProduct *ui;
};

#endif // NEWPRODUCT_H
