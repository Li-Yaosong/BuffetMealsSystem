#include "tipsdialog.h"
#include "ui_tipsdialog.h"

TipsDialog::TipsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TipsDialog)
{
    ui->setupUi(this);
}

TipsDialog::~TipsDialog()
{
    delete ui;
}
