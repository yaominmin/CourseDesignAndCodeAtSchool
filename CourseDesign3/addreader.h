#ifndef ADDREADER_H
#define ADDREADER_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QString>

namespace Ui {
class addreader;
}

class addreader : public QDialog
{
    Q_OBJECT

public:
    explicit addreader(QWidget *parent = nullptr);
    ~addreader();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addreader *ui;
};

#endif // ADDREADER_H
