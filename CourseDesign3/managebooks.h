#ifndef MANAGEBOOKS_H
#define MANAGEBOOKS_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class managebooks;
}

class managebooks : public QDialog
{
    Q_OBJECT

public:
    explicit managebooks(QWidget *parent = nullptr);
    ~managebooks();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::managebooks *ui;
};

#endif // MANAGEBOOKS_H
