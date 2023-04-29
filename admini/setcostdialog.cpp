#include "setcostdialog.h"
#include "ui_setcostdialog.h"
#include <QDate>
SetCostDialog::SetCostDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetCostDialog)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
}

SetCostDialog::~SetCostDialog()
{
    delete ui;
}

QPair<QString, double> SetCostDialog::getInfo()
{
    QPair<QString, double> ret;
    ret.first = ui->dateEdit->date().toString("yyyy-MM-dd");
    ret.second = ui->doubleSpinBox_cost->value();
    return ret;
}
