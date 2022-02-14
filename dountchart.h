#ifndef DOUNTCHART_H
#define DOUNTCHART_H

#include <QDialog>
#include"login.h"
#include"grades.h"
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>


namespace Ui {
class dountChart;
}

class dountChart : public QDialog
{
    Q_OBJECT

public:
    explicit dountChart(QWidget *parent = nullptr);
    ~dountChart();

private slots:
    void on_pushButton_clicked();

private:
    Ui::dountChart *ui;
};

#endif // DOUNTCHART_H
