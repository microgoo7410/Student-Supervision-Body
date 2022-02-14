#ifndef GRADES_H
#define GRADES_H

#include <QDialog>
#include"login.h"
#include"studentinfo.h"
#include"signup.h"
#include"dountchart.h"
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>

namespace Ui {
class Grades;
}

class Grades : public QDialog
{
    Q_OBJECT

public:
    explicit Grades(QWidget *parent = nullptr);
    ~Grades();

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_total_clicked();

    void on_pushButton_push_id_clicked();

    void on_comboBox_id_currentIndexChanged(const QString &arg1);

    void on_pushButton_Delete_clicked();

    void on_pushButton_aveg_clicked();

    void on_pushButton_chart_clicked();

private:
    Ui::Grades *ui;
};

#endif // GRADES_H
