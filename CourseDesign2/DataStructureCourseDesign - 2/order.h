#ifndef ORDER_H
#define ORDER_H
#include <QDialog>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>


namespace Ui {
class ordered;
}

class ordered : public QDialog
{
    Q_OBJECT

public:
    explicit ordered(QWidget *parent = 0);
    ~ordered();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ordered *ui;

};
#endif // ORDER_H
