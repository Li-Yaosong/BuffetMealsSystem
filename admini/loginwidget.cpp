#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "titalwidget.h"
#include "stylesheet.h"
#include "administratorinterface.h"
#include "common.h"
#include "registwidget.h"
LogInWidget::LogInWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInWidget),
    m_interface(new AdministratorInterface)
{
    ui->setupUi(this);
    TitalWidget *tital = new TitalWidget(this, QString::fromLocal8Bit("管理员登录"));
    ui->verticalLayout->insertWidget(0,tital);
    initStyle();
    connect(ui->lineEdit_admi, &QLineEdit::textChanged, this, &LogInWidget::textChanged_slot);
    connect(ui->lineEdit_pass, &QLineEdit::textChanged, this, &LogInWidget::textChanged_slot);
    ui->pushButton_login->setEnabled(false);
    ui->label_prompt->hide();
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

void LogInWidget::on_pushButton_login_clicked()
{
    Account account;
    account.usr = ui->lineEdit_admi->text();
    account.password = ui->lineEdit_pass->text();
    if(Service->accountVerification(account))
    {
        m_interface->show();
        this->hide();
    }
    else
    {
        ui->label_prompt->show();
        ui->label_prompt->setText(QStringLiteral("账户密码错误！"));
    }
}

void LogInWidget::textChanged_slot()
{
    ui->label_prompt->hide();
    QString admi = ui->lineEdit_admi->text();
    QString pass = ui->lineEdit_pass->text();
    ui->pushButton_login->setEnabled((!admi.isEmpty())&&(!pass.isEmpty()));
}


void LogInWidget::on_pushButton_regist_clicked()
{
    Account account;
    account.usr = ui->lineEdit_admi->text();
    account.password = ui->lineEdit_pass->text();

    if((!account.usr.isEmpty())&&(!account.password.isEmpty()))
    {
        if(Service->accountVerification(account))
        {
            RegistWidget *r = new RegistWidget;
            connect(r, &RegistWidget::backLogin, this,[this,r](){
                this->show();
                r->hide();
                r->deleteLater();
            });
            r->show();
            this->hide();
        }
        else
        {
            ui->label_prompt->show();
            ui->label_prompt->setText(QStringLiteral("账户密码错误！"));
        }
    }
    else
    {
        ui->label_prompt->show();
        ui->label_prompt->setText(QStringLiteral("请验证已有的管理员账户！"));
    }

}

