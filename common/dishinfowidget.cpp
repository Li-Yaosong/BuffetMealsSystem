#include "dishinfowidget.h"
#include "ui_dishinfowidget.h"
#include <QFileDialog>
#include "stylesheet.h"
DishInfoWidget::DishInfoWidget(QStringList list, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DishInfoWidget)
{
    ui->setupUi(this);
    connect(ui->lineEdit_name, &QLineEdit::textChanged, this, &DishInfoWidget::textChanged);
    connect(ui->doubleSpinBox_price, &QDoubleSpinBox::textChanged, this, &DishInfoWidget::textChanged);
    connect(ui->lineEdit_path, &QLineEdit::textChanged, this, &DishInfoWidget::textChanged);
    ui->comboBox_class->addItems(list);
    initStyle();
}

DishInfoWidget::~DishInfoWidget()
{
    delete ui;
}

QMap<QString, QByteArray> DishInfoWidget::info()
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
    if(!ui->lineEdit_name->text().isEmpty()
            && image.open(QIODevice::ReadOnly))
    {

        m_info.insert("name",ui->lineEdit_name->text().toUtf8());
        m_info.insert("price",QString::number(ui->doubleSpinBox_price->value()).toUtf8());
        m_info.insert("image",image.readAll());
        m_info.insert("class",ui->comboBox_class->currentText().toUtf8());
        emit infoChanged(m_info);
    }
    else
    {
        emit infoChanged(QMap<QString, QByteArray>());
    }
}

void DishInfoWidget::initStyle()
{
    ui->pushButton_browse->setStyleSheet(StyleSheet::buttonStyle());
    ui->label_name->setStyleSheet(StyleSheet::labelStyle(1));
    ui->label_price->setStyleSheet(StyleSheet::labelStyle(1));
    ui->label_image->setStyleSheet(StyleSheet::labelStyle(1));
    ui->label_class->setStyleSheet(StyleSheet::labelStyle(1));
    ui->label_storage->setStyleSheet(StyleSheet::labelStyle(1));
    ui->comboBox_class->setStyleSheet(StyleSheet::comboBoxStyle());
    this->setStyleSheet(StyleSheet::lineEditStyle());
}

