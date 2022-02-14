#include "grades.h"
#include "ui_grades.h"
#include<QMessageBox>
#include"dountchart.h"
Grades::Grades(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grades)
{
    ui->setupUi(this);

    QPixmap bkgnd("C:/Users/mudko/Downloads/grades.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);








    Login conn;
    if(!conn.connOpen()){
            ui->label_fourthstatus->setText("Failed to open DB");
        }else ui->label_fourthstatus->setText("Connected..");


}

Grades::~Grades()
{
    delete ui;
}

void Grades::on_pushButton_save_clicked()
{
    Login conn;

    QString ID,name,english,phy,chem,maths,sci;
    ID=ui->lineEdit_id->text();
    name=ui->lineEdit_name->text();
    english=ui->lineEdit_english->text();
    phy=ui->lineEdit_phy->text();
    chem=ui->lineEdit_che->text();
    maths=ui->lineEdit_math->text();
    sci=ui->lineEdit_science->text();


    if(!conn.connOpen()){
        qDebug()<<"Falied to Open DB";
        return;
    }

    conn.connOpen();
    QSqlQuery qr;
    qr.prepare("insert into grades (ID,Name,English,Phy,Chemistry,Maths,science) values ('"+ID+"','"+name+"','"+english+"','"+phy+"','"+chem+"','"+maths+"','"+sci+"')");

    if(qr.exec())
    {
        QMessageBox::information(this,tr("SUCCESS"),tr(" MARKS HAVE BEEN SUCCESSFULLY INSERTED IN DB"));
        conn.connClose();

    }else QMessageBox::critical(this,tr("ERROR"),qr.lastError().text());
}


void Grades::on_pushButton_back_clicked()
{
    this->hide();
    StudentInfo s;
    s.setModal(true);
    s.exec();
}

void Grades::on_pushButton_push_id_clicked()
{
    Login conn;
    QSqlQueryModel *modal=new QSqlQueryModel();

    conn.connOpen();

    QSqlQuery *qry = new QSqlQuery(conn.mydb);
    qry->prepare("select ID from grades");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox_id->setModel(modal);

    conn.connClose();
}


void Grades::on_comboBox_id_currentIndexChanged(const QString &arg1)
{
    QString name=ui->comboBox_id->currentText();

    Login conn;
    if(!conn.connOpen()){
        qDebug()<<"Falied to Open DB";
        return;
    }

    conn.connOpen();
    QSqlQuery qr;
    qr.prepare("select * from grades where ID='"+name+"'");

    if(qr.exec())
    {
        while(qr.next()){
            ui->lineEdit_id->setText(qr.value(0).toString());
            ui->lineEdit_name->setText(qr.value(1).toString());
            ui->lineEdit_english->setText(qr.value(2).toString());
            ui->lineEdit_phy->setText(qr.value(3).toString());
            ui->lineEdit_che->setText(qr.value(4).toString());
            ui->lineEdit_math->setText(qr.value(5).toString());
            ui->lineEdit_science->setText(qr.value(6).toString());
        }
        conn.connClose();

    }else QMessageBox::critical(this,tr("ERROR"),qr.lastError().text());
}


void Grades::on_pushButton_Delete_clicked()
{
    QString id=ui->comboBox_id->currentText();

    Login conn;

    if(!conn.connOpen()){
        qDebug()<<"Failed to Open DB";
        return;
    }

    conn.connOpen();
    QSqlQuery qr;
    qr.prepare("Delete from grades where ID='"+id+"'");

    if(qr.exec())
    {
        QMessageBox::information(this,tr("SUCCESS"),tr("STUDENT'S DATA DELETED SUCCESSFULLY"));
        conn.connClose();

    }else QMessageBox::critical(this,tr("ERROR"),qr.lastError().text());
}


void Grades::on_pushButton_total_clicked()
{
    Login conn;
    int eng,phy,che,maths,science;

    eng=ui->lineEdit_english->text().toInt();
    phy=ui->lineEdit_phy->text().toInt();
    che=ui->lineEdit_che->text().toInt();
    maths=ui->lineEdit_math->text().toInt();
    science=ui->lineEdit_science->text().toInt();

    QString result=QString::number(eng+phy+che+maths+science);
    ui->lineEdit_total->setText(result);


    //qulonglong number = str.toULongLong();


}


void Grades::on_pushButton_aveg_clicked()
{
    int eng,phy,che,maths,science;

    eng=ui->lineEdit_english->text().toInt();
    phy=ui->lineEdit_phy->text().toInt();
    che=ui->lineEdit_che->text().toInt();
    maths=ui->lineEdit_math->text().toInt();
    science=ui->lineEdit_science->text().toInt();

    QString result=QString::number((eng+phy+che+maths+science)/5);
    ui->lineEdit_aveg->setText(result);

    int res=ui->lineEdit_total->text().toInt();
    if(res > 450){
        QMessageBox::information(this,tr("BEST PERFORMANCE"),tr("STUDENT HAVE EXCEILLENT GRADES"));
    }else if(res < 300){
         QMessageBox::critical(this,tr("POOR PERFORMANCE"),tr("STUDENT NEED TO WORK HARD!!!"));
    }else if(res >= 300 && res <= 450) QMessageBox::information(this,tr("GOOD PERFORMANCE"),tr("STUDENT IS DOING GOOD, TRY TO DO BETTER"));

}


void Grades::on_pushButton_chart_clicked()
{

//    float english,phy,maths,chem,science;
//    english=ui->lineEdit_english->text().toFloat();
//    phy=ui->lineEdit_phy->text().toFloat();
//    maths=ui->lineEdit_math->text().toFloat();
//    chem=ui->lineEdit_che->text().toFloat();
//    science=ui->lineEdit_science->text().toFloat();

//    float total=(500-(english+phy+maths+chem+science));

    this->hide();
    dountChart d;
    d.setModal(true);
    d.exec();


}

