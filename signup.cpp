#include "signup.h"
#include "ui_signup.h"

signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);

    QPixmap bkgnd("C:/Users/mudko/Downloads/signup.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    Login conn;
    if(!conn.connOpen()){
            ui->label_thirdstatus->setText("Failed to open DB");
     }else ui->label_thirdstatus->setText("Connected..");

}

signup::~signup()
{
    delete ui;
}

void signup::on_pushButton_clicked()
{
    Login conn;

    QString username,pwd,email;
    username=ui->lineEdit_username->text();
    pwd=ui->lineEdit_pwd->text();
    email=ui->lineEdit_email->text();

    if(!conn.connOpen()){
        qDebug()<<"Falied to Open DB";
        return;
    }

    conn.connOpen();
    QSqlQuery qr;
    qr.exec("insert into login (username,password,Email) values ('"+username+"','"+pwd+"','"+email+"')");

    if(qr.exec())
    {
        QMessageBox::information(this,tr("SAVED"),tr("SUCCESSFULL SIGN_UP: YOU CAN LOGIN NOW"));
        conn.connClose();

    }else QMessageBox::critical(this,tr("ERROR"),qr.lastError().text());
}




