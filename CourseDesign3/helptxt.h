#ifndef HELPTXT_H
#define HELPTXT_H

#include <QDialog>

namespace Ui {
class helptxt;
}

class helptxt : public QDialog
{
    Q_OBJECT

public:
    explicit helptxt(QWidget *parent = nullptr);
    ~helptxt();

private:
    Ui::helptxt *ui;
};

#endif // HELPTXT_H
