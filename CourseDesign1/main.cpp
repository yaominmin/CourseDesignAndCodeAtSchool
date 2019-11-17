#include "mainwindow.h"
#include <QApplication>
#include "dboperation.h"
#include "login.h"
#include <QDebug>
#include <QMessageBox>
#include "user_dialog.h"
#include "global.h"
#include <QDebug>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!createConnection()){
        qDebug()<<"server database connection error!";
    }
//    else if(!ConnectLocalhost()){
//        qDebug()<<"local database connection error!";
//    }
    //initalization(); //初始化建表并插入测试数据
    MainWindow h;
    login w;
    QSqlQuery query12;
	query12.exec("select * from info_flight");
    if(w.exec()==QDialog::Accepted)
    {
        if(w.flag==1)   //管理员登录
            {
            h.show();
            return a.exec();
            }
        else            //用户登录
        {
			user_dialog c;
            c.show();
			return a.exec();
        }
    }
}
