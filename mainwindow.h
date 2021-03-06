#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "singup.h"
#include "admin.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_singupnow_clicked();

    void on_login_button_clicked();

protected:
    void keyPressEvent(QKeyEvent *key);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
