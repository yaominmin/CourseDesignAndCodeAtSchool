#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class accountinfo;
}

class accountinfo : public QDialog
{
    Q_OBJECT

public:
    explicit accountinfo(QWidget *parent = nullptr);
    ~accountinfo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::accountinfo *ui;
};

#endif // ACCOUNTINFO_H
