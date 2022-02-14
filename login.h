#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include<QtSql>
#include<QDebug>
#include<QFileInfo>
#include<QMessageBox>
#include"studentinfo.h"
#include"signup.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase mydb;

    void connClose(){
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen(){
        mydb=QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/Users/mudko/OneDrive/Documents/StudentInfo.sqlite");

        if(!mydb.open()){
            qDebug()<<("Failed to open DB");
            return false;
        }else{
            qDebug()<<("Connected..");
            return true;
        }
    }

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void showTime();
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_login_clicked();

    void on_pushButton_signup_clicked();

private:
    Ui::Login *ui;
};
#endif // LOGIN_H
