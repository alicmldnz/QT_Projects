#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include "secdialog.h"
namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
    ~MyDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MyDialog *ui;
    secDialog *sDialog;
};

#endif // MYDIALOG_H
