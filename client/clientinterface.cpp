#include "clientinterface.h"
#include "ui_clientinterface.h"

ClientInterface::ClientInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientInterface)
{
    ui->setupUi(this);
}

ClientInterface::~ClientInterface()
{
    delete ui;
}
