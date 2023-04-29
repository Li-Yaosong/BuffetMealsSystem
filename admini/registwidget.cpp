#include "registwidget.h"
#include "ui_registwidget.h"
#include "titalwidget.h"
#include "stylesheet.h"

RegistWidget::RegistWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistWidget)
{
    ui->setupUi(this);
    TitalWidget *tital = new TitalWidget(this, QString::fromLocal8Bit("注册管理员"));
    ui->verticalLayout->insertWidget(0,tital);
    initStyle();
}

RegistWidget::~RegistWidget()
{
    delete ui;
}

void RegistWidget::initStyle()
{
    ui->pushButton_regist->setStyleSheet(StyleSheet::buttonStyle());
    ui->label_admi->setStyleSheet(StyleSheet::labelStyle());
    ui->label_pass->setStyleSheet(StyleSheet::labelStyle());
    ui->label_confirm->setStyleSheet(StyleSheet::labelStyle());
    ui->lineEdit_admi->setStyleSheet(StyleSheet::lineEditStyle());
    ui->lineEdit_pass->setStyleSheet(StyleSheet::lineEditStyle());
    ui->lineEdit_confirm->setStyleSheet(StyleSheet::lineEditStyle());
}
