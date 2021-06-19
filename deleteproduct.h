#ifndef DELETEPRODUCT_H
#define DELETEPRODUCT_H

#include <QWidget>

namespace Ui {
class DeleteProduct;
}

class DeleteProduct : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteProduct(QWidget *parent = nullptr);
    ~DeleteProduct();

private slots:
    void on_delete_2_clicked();


private:
    Ui::DeleteProduct *ui;
};

#endif // DELETEPRODUCT_H
