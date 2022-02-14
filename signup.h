#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include"login.h"
namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_backtologin_clicked();

private:
    Ui::signup *ui;
};

#endif // SIGNUP_H
