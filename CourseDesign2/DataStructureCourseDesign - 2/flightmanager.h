#ifndef FLIGHTMANAGER_H
#define FLIGHTMANAGER_H

#endif // FLIGHTMANAGER_H
//这些都是涉及到管理员的操作和定义
//管理员1用户名为：admin1，密码为123456；
//管理员2用户名为：admin2，密码为732819；
//管理员3用户名为：admin3，密码为666666；

#include <QMap>
#include <QDate>
#include <QTime>
#include <QVector>
#include <QMainWindow>
#include <QMessageBox>
#include <doublelinklist.h>

namespace Ui
{
class FlightManager;
}

class FlightManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit FlightManager(QWidget *parent = 0);
    ~FlightManager();

public slots:
    void receive();

protected:
//    void resizeEvent(QResizeEvent*);
    void closeEvent(QCloseEvent*);

    void Init();//初始化


private slots:
    void turn2search();//查询菜单动作
    void turn2insert();//添加菜单动作
    void turn2update();//更新菜单动作
    void turn2delete();//删除菜单动作
    void turn2quit();//退出菜单动作

    void on_inserttab_tabBarClicked(int index);//点击插入面板上的标签触发的动作
    void on_newokbutton_clicked();//点击新建用户的确定按钮
    //插入面板上面标签，类似于做翻页动作
    void on_inserttab_currentChanged(int index);
    void on_chgctmnamechk_stateChanged(int arg1);
    void on_chgctmphechk_stateChanged(int arg1);
    void on_chgctmsexchk_stateChanged(int arg1);
    void on_chgctmtypchk_stateChanged(int arg1);
    void on_chgctmokbtn_clicked();
    void on_chgctmselcom_activated(int index);
    void on_chgctmselcom_activated(const QString &arg1);
    void on_chgplaneselcom_activated(int index);
    void on_chgplanelinecom_activated(int index);
    void on_chgplaneokbtn_clicked();
    void on_chgtypselcom_activated(const QString &arg1);
    void on_chgtypokbtn_clicked();
    void on_chgtktnocom_activated(int index);
    void on_chgtktlinecom_activated(int index);
    void on_chgtktokbtn_clicked();

    //更改页面中航线更改的槽
    void on_chglinecmpcek_stateChanged(int arg1);
    void on_chglinedepcek_stateChanged(int arg1);
    void on_chglinearrcek_stateChanged(int arg1);
    void on_chglinedatecek_stateChanged(int arg1);
    void on_chglinetimecek_stateChanged(int arg1);
    void on_chglineecocek_stateChanged(int arg1);
    void on_chglinebuscek_stateChanged(int arg1);
    void on_chglinedelcek_stateChanged(int arg1);
    void on_chglinenocom_activated(int index);
    void on_chglineokbtn_clicked();

    //删除页面上退票项的槽
    void on_delticketno_activated(int index);
    void on_delticketokbtn_clicked();

    void on_bktktctmno_activated(int index);

    void on_bktktdepcot_activated(const QString &arg1);

    void on_bktktarrcot_activated(const QString &arg1);

    void on_bktktarrcy_currentIndexChanged(const QString &arg1);

private:

};
