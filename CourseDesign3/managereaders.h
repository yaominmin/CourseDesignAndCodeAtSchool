#ifndef MANAGEREADERS_H
#define MANAGEREADERS_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class managereaders;
}

class managereaders : public QDialog
{
    Q_OBJECT

public:
    explicit managereaders(QWidget *parent = nullptr);
    ~managereaders();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::managereaders *ui;
};

#endif // MANAGEREADERS_H
