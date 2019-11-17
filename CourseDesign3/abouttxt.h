#ifndef ABOUTTXT_H
#define ABOUTTXT_H

#include <QDialog>

namespace Ui {
class abouttxt;
}

class abouttxt : public QDialog
{
    Q_OBJECT

public:
    explicit abouttxt(QWidget *parent = nullptr);
    ~abouttxt();

private:
    Ui::abouttxt *ui;
};

#endif // ABOUTTXT_H
