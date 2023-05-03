#include "dishinfowidget.h"
#include "ui_dishinfowidget.h"
#include <QFileDialog>
#include "stylesheet.h"
#include "common.h"
using namespace Common;
DishInfoWidget::DishInfoWidget(Dish dishInfo, QWidget *parent)
    :QWidget(parent),
    ui(new Ui::DishInfoWidget),
    m_info(dishInfo)
{
    ui->setupUi(this);
    connect(ui->lineEdit_name, &QLineEdit::textChanged, this, &DishInfoWidget::textChanged);
    connect(ui->doubleSpinBox_price, &QDoubleSpinBox::textChanged, this, &DishInfoWidget::textChanged);
    connect(ui->spinBox_storage, &QSpinBox::textChanged, this, &DishInfoWidget::textChanged);
    connect(ui->lineEdit_path, &QLineEdit::textChanged, this, &DishInfoWidget::textChanged);
    connect(ui->comboBox_class, &QComboBox::currentTextChanged, this, &DishInfoWidget::textChanged);
    ui->comboBox_class->addItems(Service->classes());
    init();
    initStyle();
}

DishInfoWidget::~DishInfoWidget()
{
    delete ui;
}

Dish DishInfoWidget::info()
{
    return m_info;
}

void DishInfoWidget::on_pushButton_browse_clicked()
{
    QString m_imagePath = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Images (*.jpg)"));

    ui->lineEdit_path->setText(m_imagePath);
    if(ui->lineEdit_name->text().isEmpty())
    {
        ui->lineEdit_name->setText(QFileInfo(m_imagePath).baseName());
    }
}

void DishInfoWidget::textChanged()
{
    QFile image = QFile(ui->lineEdit_path->text());
    if(!ui->lineEdit_name->text().isEmpty())
    {
        m_info.name = ui->lineEdit_name->text();
        m_info.price = ui->doubleSpinBox_price->value();
        m_info.className = ui->comboBox_class->currentText();
        m_info.storage = ui->spinBox_storage->value();
        if(image.open(QIODevice::ReadOnly))
        {
            m_info.image = image.readAll();
        }
        emit infoChanged(m_info);
    }
    else
    {
        emit infoChanged(Dish());
    }
}

void DishInfoWidget::initStyle()
{
    ui->pushButton_browse->setStyleSheet(StyleSheet::buttonStyle());
    ui->label_price->setStyleSheet(StyleSheet::labelStyle(1));
    ui->label_name->setStyleSheet(StyleSheet::labelStyle(1));
    ui->label_image->setStyleSheet(StyleSheet::labelStyle(1));
    ui->label_class->setStyleSheet(StyleSheet::labelStyle(1));
    ui->label_storage->setStyleSheet(StyleSheet::labelStyle(1));
//    ui->comboBox_class->setStyleSheet(StyleSheet::comboBoxStyle());
//    this->setStyleSheet(StyleSheet::lineEditStyle());
}

void DishInfoWidget::init()
{
    QString name = m_info.name;
    double price = m_info.price;
    QString className = m_info.className;
    int  storage = m_info.storage;
    ui->lineEdit_name->setText(name);
    ui->comboBox_class->setCurrentText(className);
    ui->doubleSpinBox_price->setValue(price);
    ui->spinBox_storage->setValue(storage);
}

