#include "abouttxt.h"
#include "ui_abouttxt.h"

abouttxt::abouttxt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::abouttxt)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("关于我们"));
    this->resize(500, 500);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 255, 255));
    this->setPalette(palette);
}

abouttxt::~abouttxt()
{
    delete ui;
}
