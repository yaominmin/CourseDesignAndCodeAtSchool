#include "helptxt.h"
#include "ui_helptxt.h"

helptxt::helptxt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helptxt)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("帮助文档"));
    this->resize(1200, 700);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
}

helptxt::~helptxt()
{
    delete ui;
}
