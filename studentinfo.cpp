#include "studentinfo.h"
#include "ui_studentinfo.h"

StudentInfo::StudentInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentInfo)
{
    ui->setupUi(this);

    QPixmap bkgnd("C:/Users/mudko/Downloads/stdentinfoview.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    Login conn;
    if(!conn.connOpen()){
            ui->label_sec_status->setText("Failed to open DB");
        }else ui->label_sec_status->setText("Connected..");
}

StudentInfo::~StudentInfo()
{
    delete ui;
}

void StudentInfo::on_pushButton_save_clicked()
{
    Login conn;

    QString ID,name,fname,mname,sname,dob,branch,mob,add;
    ID=ui->lineEdit_id->text();
    name=ui->lineEdit_name->text();
    fname=ui->lineEdit_fathername->text();
    mname=ui->lineEdit_mothername->text();
    sname=ui->lineEdit_surname->text();
    dob=ui->lineEdit_dob->text();
    branch=ui->lineEdit_branch->text();
    mob=ui->lineEdit_mobno->text();
    add=ui->lineEdit_address->text();

    if(!conn.connOpen()){
        qDebug()<<"Falied to Open DB";
        return;
    }

    conn.connOpen();
    QSqlQuery qr;
    qr.prepare("insert into studentview (ID,name,fathername,mothername,surname,dateofbirth,branch,mobileno,Address) values ('"+ID+"','"+name+"','"+fname+"','"+mname+"','"+sname+"','"+dob+"','"+branch+"','"+mob+"','"+add+"')");

    if(qr.exec())
    {
        QMessageBox::information(this,tr("SAVED"),tr("DATA IS SUCCESSFULLY SAVED"));
        conn.connClose();

    }else QMessageBox::critical(this,tr("ERROR"),qr.lastError().text());
}


void StudentInfo::on_pushButton_update_clicked()
{
    Login conn;

    QString ID,name,fname,mname,sname,dob,branch,mob,add;
    ID=ui->lineEdit_id->text();
    name=ui->lineEdit_name->text();
    fname=ui->lineEdit_fathername->text();
    mname=ui->lineEdit_mothername->text();
    sname=ui->lineEdit_surname->text();
    dob=ui->lineEdit_dob->text();
    branch=ui->lineEdit_branch->text();
    mob=ui->lineEdit_mobno->text();
    add=ui->lineEdit_address->text();

    if(!conn.connOpen()){
        qDebug()<<"Falied to Open DB";
        return;
    }

    conn.connOpen();
    QSqlQuery qr;
    qr.prepare("update studentview set ID='"+ID+"',name='"+name+"',fathername='"+fname+"',mothername='"+mname+"',surname='"+sname+"',dateofbirth='"+dob+"',branch='"+branch+"',mobileno='"+mob+"',Address='"+add+"' where ID='"+ID+"'");

    if(qr.exec())
    {
        QMessageBox::information(this,tr("UPDATED"),tr("DATA UPDATED SUCCESSFULLY"));
        conn.connClose();

    }else QMessageBox::critical(this,tr("ERROR"),qr.lastError().text());
}




//    QString id=ui->comboBox->;
//    QSqlQuery qr;
//    qr.prepare("delete from studentview where ID='"+id+"' ");

//    if(qr.exec())
//    {
//        QMessageBox::critical(this,tr("DELETED"),tr("ENTRY HAS BEEN SUCCESSFULLY DELETED FROM DB"));
//        conn.connClose();

//    }else QMessageBox::critical(this,tr("ERROR"),qr.lastError().text());


void StudentInfo::on_pushButton_loadtable_clicked()
{
    Login conn;
    QSqlQueryModel *modal=new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    qry->prepare("select * from studentview");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    conn.connClose();
    qDebug()<<(modal->rowCount());

}


void StudentInfo::on_pushButton_loademail_clicked()
{
    Login conn;
    QSqlQueryModel *modal=new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    qry->prepare("select surname from studentview");
    qry->exec();
    modal->setQuery(*qry);
    ui->listView->setModel(modal);

    conn.connClose();
    qDebug()<<(modal->rowCount());
}





void StudentInfo::on_pushButton_clicked()
{
    this->hide();
    Grades s;
    s.setModal(true);
    s.exec();
}

void StudentInfo::on_pushButton_studform_id_clicked()
{
    Login conn;
    QSqlQueryModel *modal=new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    qry->prepare("select ID from studentview");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox->setModel(modal);
    conn.connClose();
}



void StudentInfo::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QString name=ui->comboBox->currentText();

    Login conn;
    if(!conn.connOpen()){
        qDebug()<<"Falied to Open DB";
        return;
    }

    conn.connOpen();
    QSqlQuery qr;
    qr.prepare("select * from studentview where ID='"+name+"'");

    if(qr.exec())
    {
        while(qr.next()){
            ui->lineEdit_id->setText(qr.value(0).toString());
            ui->lineEdit_name->setText(qr.value(1).toString());
            ui->lineEdit_fathername->setText(qr.value(2).toString());
            ui->lineEdit_mothername->setText(qr.value(3).toString());
            ui->lineEdit_surname->setText(qr.value(4).toString());
            ui->lineEdit_dob->setText(qr.value(5).toString());
            ui->lineEdit_branch->setText(qr.value(6).toString());
            ui->lineEdit_mobno->setText(qr.value(7).toString());
            ui->lineEdit_address->setText(qr.value(8).toString());
        }
        conn.connClose();

    }else QMessageBox::critical(this,tr("ERROR"),qr.lastError().text());
}



void StudentInfo::on_pushButton_delete_clicked()
{
    QString id=ui->comboBox->currentText();

    Login conn;

    if(!conn.connOpen()){
        qDebug()<<"Failed to Open DB";
        return;
    }

    conn.connOpen();
    QSqlQuery qr;
    qr.prepare("Delete from studentview where ID='"+id+"'");

    if(qr.exec())
    {
        QMessageBox::information(this,tr("SUCCESS"),tr("STUDENT'S DATA DELETED SUCCESSFULLY"));
        conn.connClose();

    }else QMessageBox::critical(this,tr("ERROR"),qr.lastError().text());
}
