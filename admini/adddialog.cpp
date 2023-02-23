#include "adddialog.h"
#include "ui_adddialog.h"
#include <QFileDialog>
#include <QPushButton>
#include "titalwidget.h"
#include "stylesheet.h"
class AddDialogP
{
public:
    enum Button{
        Ok = 0,
        Cancel =1
    };
    AddDialogP()
    {

    }
    void saveButton(QPushButton * okButton, QPushButton * cancelButton)
    {
        m_okButton = okButton;
        m_cancelButton = cancelButton;
    }
    QPushButton *button(int button)
    {
        if(button == Button::Ok)
        {
            return m_okButton;
        }
        else
        {
            return m_cancelButton;
        }
    }
private:
    QPushButton * m_okButton;
    QPushButton * m_cancelButton;
};

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog),
    p(new AddDialogP)
{
    ui->setupUi(this);
    p->saveButton(ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok),
                       ui->buttonBox->button(QDialogButtonBox::StandardButton::Cancel));
    p->button(AddDialogP::Button::Ok)->setText(QString::fromLocal8Bit("确定"));
    p->button(AddDialogP::Button::Cancel)->setText(QString::fromLocal8Bit("取消"));
    p->button(AddDialogP::Button::Ok)->setStyleSheet(StyleSheet::buttonStyle());
    p->button(AddDialogP::Button::Cancel)->setStyleSheet(StyleSheet::buttonStyle());
    p->button(AddDialogP::Button::Ok)->setEnabled(false);

    TitalWidget *tital = new TitalWidget(this, QString::fromLocal8Bit("添加菜单"),0);
    ui->verticalLayout->insertWidget(0,tital);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::addWidget(QWidget *widget)
{
    ui->verticalLayout->insertWidget(1,widget);
}

void AddDialog::setOkButtonState(QMap<QString, QByteArray> info)
{
    if(info.empty())
    {
        p->button(AddDialogP::Button::Ok)->setEnabled(false);
    }
    else
    {
        p->button(AddDialogP::Button::Ok)->setEnabled(true);
    }
}
