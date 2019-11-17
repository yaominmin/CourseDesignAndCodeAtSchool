#ifndef USERCENTER_H
#define USERCENTER_H
//用户中心，选作，这个功能可以看情况实现

namespace Ui {
class UserCenter;
}

class UserCenter : public QDialog
{
    Q_OBJECT

public:
    explicit user_center(QWidget *parent = 0);
    ~user_center();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::UserCenter *ui;
};
#endif // USERCENTER_H
