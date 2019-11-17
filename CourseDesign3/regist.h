#ifndef REGIST_H
#define REGIST_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class regist;
}

class regist : public QDialog
{
    Q_OBJECT

public:
    explicit regist(QWidget *parent = nullptr);
    ~regist();

private slots:
    void on_pushButton_clicked();

private:
    Ui::regist *ui;
};

#endif // REGIST_H
