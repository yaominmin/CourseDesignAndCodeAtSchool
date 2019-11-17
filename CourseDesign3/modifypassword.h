#ifndef MODIFYPASSWORD_H
#define MODIFYPASSWORD_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class modifypassword;
}

class modifypassword : public QDialog
{
    Q_OBJECT

public:
    explicit modifypassword(QWidget *parent = nullptr);
    ~modifypassword();

private slots:
    void on_pushButton_clicked();

private:
    Ui::modifypassword *ui;
};

#endif // MODIFYPASSWORD_H
