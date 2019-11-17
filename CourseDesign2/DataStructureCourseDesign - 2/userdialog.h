#ifndef USERDIALOG_H
#define USERDIALOG_H
//用户对话框，选作，这个功能可以看情况实现

#include <QTableView>
#include <QDebug>
#include <QMessageBox>

#include <QDialog>
#include <QTimer>

class QMediaPlayer;
class QVideoWidget;

namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UserDialog(QWidget *parent = 0);
    ~UserDialog();
    int i;
    int j;
    int o;
    int checkfor;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_serachcity_clicked();
    void on_pushButton_searchnum_clicked();
    void on_btntime_clicked();
    void on_pushButton_calenda_clicked();
    void on_search_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_getflight_clicked();
    void on_getseat_clicked();
    void on_pushButton_4_clicked();
    void timeout();
protected:

private:
    Ui::UserDialog *ui;

    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QString flagsta;
    QString flagarr;
    QString flagdate;
    QString flagnum;
    QString f1;
    QString f2;
    QString f3;
    QString show0;
    QString show1;
    QString show2;
    QString show3;
    QString show4;
    QString show5;
    QString show6;
    QString show7;
    QString show8;
    QString show9;
    QTimer* timer;
    QImage images[6];
    int index;
};
#endif // USERDIALOG_H
