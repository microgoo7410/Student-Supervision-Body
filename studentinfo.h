#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QDialog>
#include "login.h"
#include"grades.h"

namespace Ui {
class StudentInfo;
}

class StudentInfo : public QDialog
{
    Q_OBJECT

public:

    explicit StudentInfo(QWidget *parent = nullptr);
    ~StudentInfo();

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_loadtable_clicked();

    void on_pushButton_loademail_clicked();

    void on_comboBox_2_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_logout_clicked();

    void on_pushButton_studform_id_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::StudentInfo *ui;
};

#endif // STUDENTINFO_H
