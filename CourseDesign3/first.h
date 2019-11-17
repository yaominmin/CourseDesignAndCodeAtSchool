#ifndef FIRST_H
#define FIRST_H

#include <QDialog>
#include <mainwindow.h>
#include <regist.h>
#include <user.h>

namespace Ui {
class First;
}

class First : public QDialog
{
    Q_OBJECT

public:
    explicit First(QWidget *parent = nullptr);
    ~First();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::First *ui;
    MainWindow w;
};

#endif // FIRST_H
