#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <modifypassword.h>
#include <addreader.h>
#include <addbook.h>
#include <borrowbook.h>
#include <returnbook.h>
#include <accountinfo.h>
#include <managereaders.h>
#include <managebooks.h>
#include <helptxt.h>
#include <abouttxt.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

signals:
    void sendData(QStringList*);
private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_modifyinfo_triggered();

    void on_modifypassword_triggered();

    void on_addreader_triggered();

    void on_managereaders_triggered();

    void on_addbook_triggered();

    void on_managebooks_triggered();

    void on_help_triggered();

    void on_about_triggered();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
