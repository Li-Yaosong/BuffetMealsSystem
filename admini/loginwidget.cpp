#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "titalwidget.h"
#include "stylesheet.h"
LogInWidget::LogInWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInWidget)
{
    ui->setupUi(this);
    TitalWidget *tital = new TitalWidget(this, QString::fromLocal8Bit("管理员登录"));
    ui->verticalLayout->insertWidget(0,tital);
    initStyle();
}

LogInWidget::~LogInWidget()
{
    delete ui;
}

void LogInWidget::initStyle()
{
    ui->pushButton_login->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_regist->setStyleSheet(StyleSheet::buttonStyle());
    ui->label_admi->setStyleSheet(StyleSheet::labelStyle());
    ui->label_pass->setStyleSheet(StyleSheet::labelStyle());
    ui->lineEdit_admi->setStyleSheet(StyleSheet::lineEditStyle());
    ui->lineEdit_pass->setStyleSheet(StyleSheet::lineEditStyle());
}
