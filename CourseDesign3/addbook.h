#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class addbook;
}

class addbook : public QDialog
{
    Q_OBJECT

public:
    explicit addbook(QWidget *parent = nullptr);
    ~addbook();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addbook *ui;
};

#endif // ADDBOOK_H
