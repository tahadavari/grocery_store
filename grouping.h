#ifndef GROUPING_H
#define GROUPING_H

#include <QWidget>

namespace Ui {
class Grouping;
}

class Grouping : public QWidget
{
    Q_OBJECT

public:
    explicit Grouping(QWidget *parent = nullptr);
    ~Grouping();

private slots:
    void on_add_clicked();

private:
    Ui::Grouping *ui;
};

#endif // GROUPING_H
