#include "dountchart.h"
#include "ui_dountchart.h"
#include"grades.h"
dountChart::dountChart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dountChart)
{
    ui->setupUi(this);



    QPieSeries *series= new QPieSeries();
    series->setHoleSize(0.25);
    series->append("ENGLISH",10);
    series->append("PHYSICS",10);
    series->append("MATHS",14);
    series->append("CHEMISTRY",14);
    QPieSlice *slice = series->append("SCIENCE",12);

    slice->setExploded();
    slice->setLabelVisible();

    series->append("REMAINING MARKS",40);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("STUDENT PERFORMANCE CHART");

    QChartView *chartview= new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);

    chartview->setParent(ui->horizontalFrame);
}

dountChart::~dountChart()
{
    delete ui;
}

void dountChart::on_pushButton_clicked()
{
    this->hide();
    Grades g;
    g.setModal(true);
    g.exec();
}

