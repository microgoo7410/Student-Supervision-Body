#include "login.h"
#include "ui_login.h"
#include<QTimer>
#include<QDateTime>
#include<QMessageBox>
Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);


//    mydb=QSqlDatabase::addDatabase("QSQLITE");
//    mydb.setDatabaseName("C:/Users/mudko/OneDrive/Documents/StudentInfo.sqlite");


    QPixmap bkgnd("C:/Users/mudko/Downloads/vector.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);


    if(!connOpen()){
        ui->label->setText("Failed to open DB");
    }else ui->label->setText("Connected..");


    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();

}
void Login::showTime(){

    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");

    if((time.second()%2)==0){
        time_text[3]=' ';
        time_text[8]=' ';
    }
    ui->label_clock->setText(time_text);
}
Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    QString username,password;
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_pwd->text();

    if(!connOpen()){
        qDebug()<<"Falied to Open DB";
        return;
    }

    connOpen();
    QSqlQuery qr;
    qr.prepare("select * from login where username='"+username+"' and password='"+password+"'");

    if(qr.exec())
    {
        int count=0;
        while(qr.next()){
            count++;
        }
        if(count==1){
            QMessageBox::information(this,tr("LOGGED-IN"),tr("SUCCESS!!"));

            connClose();
            this->hide();
            StudentInfo studentinfo;
            studentinfo.setModal(true);
            studentinfo.exec();
        }
        if(count>1) QMessageBox::critical(this,tr("ERROR"),tr("DUPLICATE ALERT!!"));

        if(count<1) QMessageBox::critical(this,tr("ERROR"),tr("SIGN - UP FOR LOGIN!!"));
    }
}




void Login::on_pushButton_signup_clicked()
{
    this->hide();
    signup s;
    s.setModal(true);
    s.exec();
}

