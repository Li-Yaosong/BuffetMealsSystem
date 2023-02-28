#include "classbutton.h"
#include "ui_classbutton.h"

ClassButton::ClassButton(QString name, QIcon icon, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClassButton)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->pushButton->setIcon(icon);
}

ClassButton::~ClassButton()
{
    delete ui;
}

QPushButton *ClassButton::button()
{
    return ui->pushButton;
}
