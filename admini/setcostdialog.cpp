#include "setcostdialog.h"
#include "ui_setcostdialog.h"
#include <QDate>
#include "titalwidget.h"
#include <QPushButton>
SetCostDialog::SetCostDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetCostDialog)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    TitalWidget *tital= new TitalWidget(this, QStringLiteral("成本设置"), false);
    ui->verticalLayout->insertWidget(0, tital);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(QStringLiteral("完成"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(QStringLiteral("取消"));
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
