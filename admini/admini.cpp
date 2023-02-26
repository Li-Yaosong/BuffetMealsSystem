#include "admini.h"
#include "ui_admini.h"

Admini::Admini(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Admini)
{
    ui->setupUi(this);
}

Admini::~Admini()
{
    delete ui;
}

