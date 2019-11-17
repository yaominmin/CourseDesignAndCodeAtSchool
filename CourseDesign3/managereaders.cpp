#include "managereaders.h"
#include "ui_managereaders.h"
#include "QComboBox"
#include "librarian.h"

managereaders::managereaders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managereaders)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("管理读者信息"));
    this->resize(880, 500);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
    QIcon ico("://v.png");
    ui->pushButton_2->setIcon(ico);
    ui->pushButton_2->setIconSize(QSize(50,50));
    QIcon ico_1("://o.png");
    ui->pushButton_4->setIcon(ico_1);
    ui->pushButton_4->setIconSize(QSize(50,50));
    QIcon ico_2("://b.png");
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_5->setIcon(ico_2);
    ui->pushButton_5->setIconSize(QSize(50,50));
    ui->lineEdit->setPlaceholderText("：输入信息进行检索");
    ui->tableWidget->setStyleSheet("selection-background-color:lightblue;");
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pushButton_5->setToolTip("按住CTRL进行多选");
    ui->pushButton_2->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
    ui->pushButton_4->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
    ui->pushButton_5->setStyleSheet("QPushButton{background-color:white;\
                              color: black;   border-radius: 10px;  border: 2px groove gray;\
                              border-style: outset;}"
                              "QPushButton:hover{background-color:black; color: white;}");
}

managereaders::~managereaders()
{
    delete ui;
}

void managereaders::on_pushButton_5_clicked()
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    if(!focus){
        QMessageBox::critical(this,"失败提示","请在检索并选中读者后进行操作！",QMessageBox::Ok);
    }
    else{
        QMessageBox messageBox(QMessageBox::NoIcon,
                                  "删除", "你确定要删除吗?",
                                  QMessageBox::Yes | QMessageBox::No, NULL); ;
           int result=messageBox.exec();
           switch (result)
           {
           case QMessageBox::Yes:{
               QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
               int t=-1;
               int count=ranges.count();
               int select[20];
               for(int i=0;i<20;i++)
                   select[i]=-1;
               for(int i=0;i<count;i++)
                   select[i]=ranges.at(i).topRow();
               for(int i=count-1;i>=0;i--){
                   QTableWidgetItem *userID=new QTableWidgetItem();
                   userID=ui->tableWidget->item(select[i],0);
                   Librarian lib;
                   t=lib.deleReaderInfo(userID->text());
               }
               if(t!=1){
                   QMessageBox::critical(this,"失败提示","不可删除！该读者已借阅过图书！",QMessageBox::Ok);
               }
               else{
                   for(int i=count-1;i>=0;i--){
                       ui->tableWidget->setItem(select[i],0,NULL);
                       ui->tableWidget->setItem(select[i],1,NULL);
                       ui->tableWidget->setItem(select[i],2,NULL);
                       ui->tableWidget->setItem(select[i],3,NULL);
                       ui->tableWidget->setItem(select[i],4,NULL);
                       ui->tableWidget->setItem(select[i],5,NULL);
                   }
               }
               break;
               }
           case QMessageBox::No:
               break;
           default:
               break;
           }
    }
}

void managereaders::on_pushButton_4_clicked()
{
    bool focus = ui->tableWidget->isItemSelected(ui->tableWidget->currentItem());
    if(!focus){
        QMessageBox::critical(this,"失败提示","请在检索并修改后进行操作！",QMessageBox::Ok);
    }
    else{
        QTableWidgetItem f;
        f.setText("");
        for(int i=0;i<20;i++)
        {
            if(ui->tableWidget->item(i,0)==NULL||ui->tableWidget->item(i,1)==NULL||ui->tableWidget->item(i,0)->text()==f.text()||ui->tableWidget->item(i,1)->text()==f.text())
                continue;
            if(ui->tableWidget->item(i,2)==NULL||ui->tableWidget->item(i,3)==NULL||ui->tableWidget->item(i,2)->text()==f.text()||ui->tableWidget->item(i,3)->text()==f.text())
                continue;
            if(ui->tableWidget->item(i,4)==NULL||ui->tableWidget->item(i,5)==NULL||ui->tableWidget->item(i,4)->text()==f.text()||ui->tableWidget->item(i,5)->text()==f.text())
                continue;
            QTableWidgetItem *c=new QTableWidgetItem();
            c=ui->tableWidget->item(i,0);
            QTableWidgetItem *d=new QTableWidgetItem();
            d=ui->tableWidget->item(i,1);
            QTableWidgetItem *e=new QTableWidgetItem();
            e=ui->tableWidget->item(i,2);
            QTableWidgetItem *g=new QTableWidgetItem();
            g=ui->tableWidget->item(i,3);
            QTableWidgetItem *h=new QTableWidgetItem();
            h=ui->tableWidget->item(i,4);
            QTableWidgetItem *k=new QTableWidgetItem();
            k=ui->tableWidget->item(i,5);
            QString userID=c->text();
            QString name=d->text();
            QString sex=e->text();
            QString dept=g->text();
            QString type=h->text();
            QString status=k->text();
            Librarian *library=new Librarian();
            library->changeReaderInfo(userID,name,sex,dept,type,status);
        }
            QMessageBox::information(this,"更改成功","已成功更改符合规范的读者信息！",QMessageBox::Ok);
    }
}

void managereaders::on_pushButton_2_clicked()
{
    QString a;
    int b=0;
    //返回值
    int c=-1;
    //创建指针数组，并分配空间
    Reader *reader[100];
    for(int i=0;i<100;i++)
    {
        reader[i]=new Reader();
    }
    //读取输入框内容
    a = ui->lineEdit->text();
    //读取下拉框内容
    b = ui->comboBox->currentIndex();
    //船舰管理员对象，调用他的函数
    Librarian lib;
    switch (b){
    case 0:
        c = lib.selectReaderByID(a,reader);
        break;
    case 1:
        c = lib.selectReaderByName(a,reader);
        break;
    }
    if(reader[0]==nullptr){
        QMessageBox::warning(this,"查找失败","未查询到相关读者！",QMessageBox::Ok);
    }
    if(c==0){
        QMessageBox::critical(this,"查找失败","查询出错！",QMessageBox::Ok);
    }
    for(int i=0;i<100;i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(reader[i]->getUserID()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(reader[i]->getName()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(reader[i]->getGender()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(reader[i]->getDept()));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(reader[i]->getType()));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(reader[i]->getStatus()));
    }
}
