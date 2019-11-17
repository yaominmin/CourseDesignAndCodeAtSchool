#ifndef FLIGHTMANAGER_H
#define FLIGHTMANAGER_H

#endif // FLIGHTMANAGER_H
//��Щ�����漰������Ա�Ĳ����Ͷ���
//����Ա1�û���Ϊ��admin1������Ϊ123456��
//����Ա2�û���Ϊ��admin2������Ϊ732819��
//����Ա3�û���Ϊ��admin3������Ϊ666666��

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

    void Init();//��ʼ��


private slots:
    void turn2search();//��ѯ�˵�����
    void turn2insert();//��Ӳ˵�����
    void turn2update();//���²˵�����
    void turn2delete();//ɾ���˵�����
    void turn2quit();//�˳��˵�����

    void on_inserttab_tabBarClicked(int index);//�����������ϵı�ǩ�����Ķ���
    void on_newokbutton_clicked();//����½��û���ȷ����ť
    //������������ǩ������������ҳ����
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

    //����ҳ���к��߸��ĵĲ�
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

    //ɾ��ҳ������Ʊ��Ĳ�
    void on_delticketno_activated(int index);
    void on_delticketokbtn_clicked();

    void on_bktktctmno_activated(int index);

    void on_bktktdepcot_activated(const QString &arg1);

    void on_bktktarrcot_activated(const QString &arg1);

    void on_bktktarrcy_currentIndexChanged(const QString &arg1);

private:

};
