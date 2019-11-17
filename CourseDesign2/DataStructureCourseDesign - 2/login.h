#ifndef LOGIN_H
#define LOGIN_H
#include <QDialog>
#include <QMessageBox>
#include <doublelinklist.h>
#include <cstdlib>

//�ͻ��˵�¼����Ҫ�Ķ���ͺ���

namespace Ui
{
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    void dosend();

signals:
    void send();

protected:
    int CheckWriting();//�鿴�˺��������Ƿ�Ϊ��
    int CheckAccount();//�鿴�˺������Ƿ���ȷ
    //unsigned int BKDRHash(char* str);//���ù�ϣ�������������

    //��
private slots:
    void on_quitbutton_clicked();//����˳���ť�������ķ�Ӧ
    void on_loginbutton_clicked();//�����½�������ķ�Ӧ

private:
    enum LoginType { Success, WebError, AccountBlank, AccountWrong, PasswordBlank, PasswordWrong, RepeatError };

private:
    Ui::Login* ui;
};


#endif // LOGIN_H
