#ifndef USERCENTER_H
#define USERCENTER_H
//�û����ģ�ѡ����������ܿ��Կ����ʵ��

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
