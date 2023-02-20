#include "dishinfowidget.h"
#include "ui_dishinfowidget.h"
#include <QFileDialog>
DishInfoWidget::DishInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DishInfoWidget)
{
    ui->setupUi(this);
    connect(ui->lineEdit_name, &QLineEdit::textChanged, this, &DishInfoWidget::infoChanged);
    connect(ui->doubleSpinBox_price, &QDoubleSpinBox::textChanged, this, &DishInfoWidget::infoChanged);
    connect(ui->lineEdit_path, &QLineEdit::textChanged, this, &DishInfoWidget::infoChanged);
}

DishInfoWidget::~DishInfoWidget()
{
    delete ui;
}

DishInfoWidget::DishInfo DishInfoWidget::info()
{
    DishInfo info;
    info.name = ui->lineEdit_name->text();
    info.price = ui->doubleSpinBox_price->value();
    info.imagePath = ui->lineEdit_path->text();
    return info;
}

void DishInfoWidget::on_pushButton_browse_clicked()
{
    QString m_imagePath = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Images (*.jpg)"));
    ui->lineEdit_path->setText(m_imagePath);
}

