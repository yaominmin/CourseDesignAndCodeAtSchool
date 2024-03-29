﻿#include "user_dialog.h"
#include "ui_user_dialog.h"
#include "login.h"
#include "ordered.h"
#include "global.h"

#include <QErrorMessage>
#include <QSqlQuery>
#include <QDebug>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QLabel>
#include <QMovie>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QVideoWidget>
#include <QString>
#include <QDate>


//默认城市搜索
QString GoPlace;        //给机票信息窗口传送地名
QString ToPlace;
QString GoTimes;
QString hangbanNum;        //给机票信息窗口传送地名
//记录日历点击次数
user_dialog::user_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_dialog)
{
    int o=1;
    checkfor=1;
    this->setWindowIcon(QIcon(":/images/bitbug_favicon.ico"));
    ui->setupUi(this);
    returnLogin = new login;

    QDate date = QDate::currentDate();
    ui->calendarWidget->setMinimumDate(QDate::currentDate());//设置最小时间是当前时间
    ui->calendarWidget->setMaximumDate(date.addMonths(3));//设置最长订票日期3个月之后

    model3=new QSqlTableModel(this);
    model3->setTable("info_seat");
    model3->setFilter(QString("id = '%1'").arg(""));
    model3->select();
    model3->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_showticket->setModel(model3);
    ui->tableView_showticket->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置表格列宽度自适应
    ui->tableView_showticket->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableView_showticket->resizeColumnsToContents();
    ui->tableView_showticket->hideColumn(5);
    ui->tableView_showticket->hideColumn(4);
    ui->tableView_showticket->verticalHeader()->setVisible(false);
    ui->tableView_showticket->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->tableView_showticket->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_showticket->horizontalHeader()->setStyleSheet
            ("QHeaderView::section {background-color:lightblue;"
             "color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");
    ui->tableView_showticket->setAlternatingRowColors(true);
    ui->tableView_showticket->setFocusPolicy(Qt::NoFocus); //去除选中虚线框
    model5 = new QSqlTableModel(this);
    model5->setTable("info_flight");
    model5->select();
    ui->tableView_buy->setModel(model5);
    model5->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView_buy->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置表格列宽度自适应

    ui->tableView_buy->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableView_buy->resizeColumnsToContents();
    ui->tableView_buy->verticalHeader()->setVisible(false);
    ui->tableView_buy->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->tableView_buy->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_buy
            ->horizontalHeader()
            ->setStyleSheet
            ("QHeaderView::section"
             "{background-color: qlineargradient"
             "(x1:0, y1:0, x2:0, y2:1, "
             "stop:0 rgb(46,46,46),"
             "stop:1 rgb(66,66,66));"
             "color: rgb(210,210,210);;"
             "padding-left: 4px;border: 1px solid #383838;}"); //设置表头背景色
    ui->tableView_buy->setAlternatingRowColors(true);//使用交替行颜色
    ui->tableView_buy->setFocusPolicy(Qt::NoFocus); //去除选中虚线框
    ui->tableView_buy->hideColumn(6);
    ui->tableView_buy->hideColumn(3);
    ui->tableView_buy->hideColumn(2);
    //ui->lab->setText(userinfo);
    //ui->pushButton_serachcity->setEnabled(false); //初始设置城市搜索为不可按
    //ui->pushButton_searchnum->setEnabled(true);
    //ui->dateEdit->setEditable(true); //设置选择航班号QComboBox可编辑
    //ui->pushButton_2->hide();
    ui->getseat->show();
    ui->search->show();
    ui->getflight->show();
    //ui->dateEdit->hide();
    ui->label_5->hide();
    ui->calendarWidget->hide();
    ui->pushButton_calenda->hide();
    //ui->pushButton_serachcity->setFocus();
    ui->comboBox->setEditable(true);     //下拉框可编辑
    ui->comboBox_2->setEditable(true);
    QString place = "合肥,北京,上海,深圳,香港";      //添加默认热门城市
    QString place1 =  "上海,合肥,北京,深圳,香港";
    QStringList places = place.split(",",QString::SkipEmptyParts);
    QStringList places1 = place1.split(",",QString::SkipEmptyParts);
    ui->comboBox->addItems(places);
    ui->comboBox_2->addItems(places1);
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString strTime = time.toString("yyyy-MM-dd");//设("yyyy-MM-dd");设置系统时间显示格式
    ui->label_show->setStyleSheet("border-image: url(:/images/5.jpg)");
    ui->label_show->show();
    images[0] = QImage(":/images/0.jpg");
    images[1] = QImage(":/images/1.jpg");
    images[2] = QImage(":/images/2.jpgg");
    images[3] = QImage(":/images/3.jpg");
    images[4] = QImage(":/images/4.jpg");
    images[5] = QImage(":/images/5.jpg");
    index = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start(3000);
}

user_dialog::~user_dialog()
{
    delete ui;
}
void user_dialog::on_pushButton_clicked()
{
//    user_center d;
//    d.exec();
}

void user_dialog::on_pushButton_serachcity_clicked()
{
    checkfor=1;  //选择城市查询
    //ui->pushButton_2->hide();
    ui->getseat->show();
    ui->search->show();
    ui->getflight->show();
    ui->tableView_buy->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();
    ui->comboBox->show();
    ui->comboBox_2->show();
    ui->lineEdit_time->show();
    ui->btntime->show();
    //ui->dateEdit->hide();
    ui->label_5->hide();
    //ui->pushButton_serachcity->setEnabled(false);
    //ui->pushButton_searchnum->setEnabled(true);
    ui->label_show->show();
}
void user_dialog::timeout()
{
    index++;
    QString url;
    url="border-image: url(:/images/"+QString::number(index%5,10)+".jpg)";
    ui->label_show->setStyleSheet(url);
}

void user_dialog::on_pushButton_searchnum_clicked()
{
    ui->label_show->show();
    checkfor=0;//选择航班号查询
    ui->getseat->show();
    //ui->pushButton_2->show();
    ui->search->hide();
    ui->getflight->hide();
    ui->tableView_buy->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->show();
    ui->comboBox->hide();
    ui->comboBox_2->hide();
    ui->lineEdit_time->show();
    ui->btntime->show();
    //ui->dateEdit->show();
    ui->label_5->show();
    //ui->pushButton_serachcity->setEnabled(true); //初始设置城市搜索为不可按
    //ui->pushButton_searchnum->setEnabled(false);
}


void user_dialog::on_btntime_clicked()
{
    // o=o+1;
    if(o % 2 == 0)
    {
        //选择时间时，下面控件隐藏
        //j本身为1，当点击偶数次，日历显示
        ui->calendarWidget->show();
        ui->pushButton_calenda->show();
        ui->lineEdit_time->setText(ui->calendarWidget->selectedDate().toString("yyyy-MM-dd"));
    }
    else
    {
        //点击奇数次，日历隐藏
        ui->calendarWidget->hide();
        ui->pushButton_calenda->hide();
        ui->lineEdit_time->setText(ui->calendarWidget->selectedDate().toString("yyyy-MM-dd"));
    }
}

void user_dialog::on_pushButton_calenda_clicked()
{
    o=o+1;
    ui->lineEdit_time->setText(ui->calendarWidget->selectedDate().toString("yyyy-MM-dd"));
    ui->calendarWidget->hide();
    ui->pushButton_calenda->hide();
}

//查询航班信息按钮
void user_dialog::on_search_clicked()
{
    QString flagsta = ui->comboBox->currentText();
    QString flagarr = ui->comboBox_2->currentText();
    //QString flagnum=ui->dateEdit->currentText();
    QString flagdate=ui->lineEdit_time->text();
    ui->tableView_buy->show();
    if(checkfor==1)           //按城市搜索
//"110" "HU7604" "合肥" "上海" "合肥新桥机场" "上海虹桥机场" "2019-01-01" "9:30" "10:50:00" "1000"
// Fid,Aircraftid,Fstar,Fend,AirportS,AirportE,sdate date,Fstarttime time,Fendtime time,Fmoney float
    {
        if(flagsta.isEmpty() || flagarr.isEmpty() || flagdate.isEmpty())
        {
            QMessageBox::information(this,tr("亲爱的旅客%1").arg(userinfo),
                                     tr("请输入完整信息,起点终点日期!"),QMessageBox::Ok);
        }
        else                                  //城市搜索和日期都不为空
        {
            ui->label_show->hide();
            //现在根据出发到达日期在info_flight表中查询航班的Fid,Aircrafid,sdate
            //获得Fid,Aircrafid,sdate在model查询获得座位
            QString start=ui->comboBox->currentText();
            QString Fend=ui->comboBox_2->currentText();
            QString sdate=ui->lineEdit_time->text();
            QSqlQuery query15;
            model5->setFilter
                    (QString("Fstart = '%1' AND Fend= '%2' AND sdate='%3'")
                     .arg(start).arg(Fend).arg(sdate));
            model5->select();
        }
    }
    else           //按航班号搜索
    {
        if(flagnum.isEmpty() || flagdate.isEmpty())
        {
            QMessageBox::information(this,tr("亲爱的旅客%1").arg(userinfo),
                                     tr("请输入完整信息,起航班号日期!"),QMessageBox::Ok);
        }
    }
}

void user_dialog::on_pushButton_2_clicked()
{
    ui->label_show->hide();
    //int rowidx = ui->tableView_showticket->selectionModel()->currentIndex().row();
//    model3->setFilter
//            (QString("Aircraftid = '%1' and sdate = '%2' AND id= '%3'")
//             .arg(ui->dateEdit->currentText()).arg(ui->lineEdit_time->text()).arg(""));
    model3->select();
    //qDebug()<<model3->index(rowidx,1).data().toString();  //获取选定行某列的数据
}

void user_dialog::on_getflight_clicked()
{
    int getflight_rowidx = ui->tableView_buy->selectionModel()->currentIndex().row();
    if(model3->index(getflight_rowidx,0).data().toString()=="")
    {
        QMessageBox::information(NULL, QString("错啦"), QString("没有该航班，请重新查询"));
    }
    else
    {
        if(checkfor==1)
        {
            int getflight_rowidx = ui->tableView_buy->selectionModel()->currentIndex().row();
            QString hh1=model5->index(getflight_rowidx,0).data().toString();
            QString hh2=model5->index(getflight_rowidx,1).data().toString();
            QString hh3=model5->index(getflight_rowidx,6).data().toString();
            show0=model5->index(getflight_rowidx,0).data().toString();
            show1=model5->index(getflight_rowidx,1).data().toString();
            show2=model5->index(getflight_rowidx,2).data().toString();
            show3=model5->index(getflight_rowidx,3).data().toString();
            show4=model5->index(getflight_rowidx,4).data().toString();
            show5=model5->index(getflight_rowidx,5).data().toString();
            show6=model5->index(getflight_rowidx,6).data().toString();
            show7=model5->index(getflight_rowidx,7).data().toString();
            show8=model5->index(getflight_rowidx,8).data().toString();
            model3->setFilter(QString("Fid = '%1' AND id = '%2'").arg(hh1).arg(""));
            model3->select();
            ui->tableView_buy->hide();
        }
    }
}

void user_dialog::on_getseat_clicked()
{
    int showticket_curRow = ui->tableView_showticket->currentIndex().row();
    if(model3->index(showticket_curRow,0).data().toString()=="")
    {
        QMessageBox::information(NULL, QString("错啦"), QString("没有该航班，请重新查询"));
        //
        if(checkfor==0)
        {
            ui->label_show->show();
        }

    }
    else
    {
        model3->setData(model3->index(showticket_curRow, 5), userinfo);
        //show9="2019-01-01";
        show9=model3->index(showticket_curRow,0).data().toString();  //获得购买的航班座位
        QMessageBox::information(NULL,
                                 QString("恭喜"),
                                 QString(tr("尊敬的客户")
                                         +userinfo
                                         +tr("\n您已经购买从")
                                         +show2
                                         +tr("到")
                                         +show3
                                         +tr("\n")
                                         +show4
                                         +tr("到")
                                         +show5
                                         +tr("的")
                                         +show1
                                         +tr("次航班\n登机时间为")
                                         +show6
                                         +tr("的")
                                         +show7
                                         +tr("分")
                                         +tr(".\n中国南方航空祝您旅途愉快！！  "
                                             "24小时人工客服热线：95530,"
                                             "vip客户专属服务热线：96300")));
        // 可以直接提交
        model3->submitAll();
        model3->select();
        ui->label_show->show();
    }
}

void user_dialog::on_pushButton_3_clicked()
{
    show0="";
    show1="";
    show2="";
    show3="";
    show4="";
    show5="";
    show6="";
    show7="";
    show8="";
    if(checkfor==1)
    {
        ui->label_show->show();
        //ui->pushButton_2->hide();
        ui->getseat->show();
        ui->search->show();
        ui->getflight->show();
        //ui->dateEdit->hide();
        ui->label_5->hide();
        ui->calendarWidget->hide();
        ui->pushButton_calenda->hide();
    }
    else
    {
        ui->label_show->show();
        ui->search->hide();
        ui->getflight->hide();
        //ui->pushButton_2->show();
        ui->getseat->show();

    }
}

void user_dialog::on_pushButton_4_clicked()
{
    ordered order;
    order.exec();
}

