#include "dishwidget.h"
#include "ui_dishwidget.h"

DishWidget::DishWidget(QWidget *parent, QMap<QString, QVariant> data) :
    QWidget(parent),
    ui(new Ui::DishWidget)
{
    ui->setupUi(this);
    ui->checkBox->hide();
    m_imageW = new ImageWidget(nullptr, data.value("image").toByteArray());
    QString name = QString(data.value("name").toByteArray());
    setNum(QString(data.value("number").toByteArray()));
    setName(name);
    setPrice(data.value("price").toDouble());
    setStorage(data.value("storage").toString());
    connect(ui->checkBox, &QCheckBox::stateChanged,this, [this]{
        if(ui->checkBox->isCheckable())
        {
            emit checkBoxStateChanged(ui->label_name->text(),true);
        }
        else
        {
            emit checkBoxStateChanged(ui->label_name->text(),false);
        }
    });
}

DishWidget::~DishWidget()
{
    delete ui;
}

void DishWidget::setNum(const QString &num)
{
    ui->label_num->setText(num);
}

void DishWidget::setName(const QString &name)
{
    ui->label_name->setText(name);
}

void DishWidget::setPrice(const double &price)
{
    ui->label_price->setText(QString::number(price));
}

void DishWidget::setStorage(const QString &storage)
{
    if(storage == "yes")
    {
        ui->label_storage->setText(QString::fromLocal8Bit("enough"));
    }
    else
    {
        ui->label_storage->setText(QString::fromLocal8Bit("Not enough"));
    }
}

void DishWidget::showCheckBox()
{
    ui->checkBox->show();
}

void DishWidget::hideCheckBox()
{
    ui->checkBox->hide();
}

void DishWidget::on_pushButton_clicked()
{
    m_imageW->show();
}

