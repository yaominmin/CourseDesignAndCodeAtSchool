#ifndef BORROWBOOK_H
#define BORROWBOOK_H

#include <QDialog>

namespace Ui {
class borrowbook;
}

class borrowbook : public QDialog
{
    Q_OBJECT

public:
    explicit borrowbook(QWidget *parent = nullptr);
    ~borrowbook();
    QStringList *date;
private slots:
    void receiveData(QStringList* data);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::borrowbook *ui;
};

#endif // BORROWBOOK_H
