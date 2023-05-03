#include "registwidget.h"
#include "ui_registwidget.h"
#include "titalwidget.h"
#include "stylesheet.h"
#include "common.h"

RegistWidget::RegistWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistWidget)
{
    ui->setupUi(this);
    TitalWidget *tital = new TitalWidget(this, QString::fromLocal8Bit("注册管理员"));
    ui->verticalLayout->insertWidget(0,tital);
    initStyle();
    connect(ui->pushButton_back, &QPushButton::clicked, this, &RegistWidget::backLogin);
    connect(ui->lineEdit_admi, &QLineEdit::textChanged, this, &RegistWidget::textChanged_slot);
    connect(ui->lineEdit_pass, &QLineEdit::textChanged, this, &RegistWidget::textChanged_slot);
    connect(ui->lineEdit_confirm, &QLineEdit::textChanged, this, &RegistWidget::textChanged_slot);
}

RegistWidget::~RegistWidget()
{
    delete ui;
}

void RegistWidget::initStyle()
{
    ui->pushButton_regist->setStyleSheet(StyleSheet::buttonStyle());
    ui->pushButton_back->setStyleSheet(StyleSheet::buttonStyle());
    ui->label_admi->setStyleSheet(StyleSheet::labelStyle());
    ui->label_pass->setStyleSheet(StyleSheet::labelStyle());
    ui->label_confirm->setStyleSheet(StyleSheet::labelStyle());
    ui->lineEdit_admi->setStyleSheet(StyleSheet::lineEditStyle());
    ui->lineEdit_pass->setStyleSheet(StyleSheet::lineEditStyle());
    ui->lineEdit_confirm->setStyleSheet(StyleSheet::lineEditStyle());
}

void RegistWidget::on_pushButton_regist_clicked()
{
    if(ui->lineEdit_admi->text().isEmpty())
    {
        ui->label_prompt->show();
        ui->label_prompt->setText(QStringLiteral("请输入用户名"));
        return;
    }
    if(ui->lineEdit_pass->text().isEmpty())
    {
        ui->label_prompt->show();
        ui->label_prompt->setText(QStringLiteral("请输入密码"));
        return;
    }
    if(ui->lineEdit_pass->text() != ui->lineEdit_confirm->text())
    {
        ui->label_prompt->show();
        ui->label_prompt->setText(QStringLiteral("两次输入的密码不一致"));
        return;
    }
    Account account;
    account.usr = ui->lineEdit_admi->text();
    account.password = ui->lineEdit_pass->text();
    if(Service->registerAccount(account))
    {
        ui->label_prompt->show();
        ui->label_prompt->setText(QStringLiteral("注册成功！"));
        return;
    }
    else
    {
        ui->label_prompt->show();
        ui->label_prompt->setText(QStringLiteral("用户已存在，注册失败！"));
        return;
    }
}

void RegistWidget::textChanged_slot()
{
    ui->label_prompt->hide();
}

