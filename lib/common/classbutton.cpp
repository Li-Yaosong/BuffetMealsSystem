#include "classbutton.h"
#include "ui_classbutton.h"
#include "stylesheet.h"
ClassButton::ClassButton(QString name, QIcon icon, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClassButton)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setStyleSheet(StyleSheet::labelStyle(0));
    ui->pushButton->setIcon(icon);
    ui->pushButton->setIconSize(ui->pushButton->size());
}

ClassButton::~ClassButton()
{
    delete ui;
}

QPushButton *ClassButton::button()
{
    return ui->pushButton;
}
