#include "classinfowidget.h"
#include "ui_classinfowidget.h"
#include <QFileDialog>
#include "stylesheet.h"
ClassInfoWidget::ClassInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClassInfoWidget)
{
    ui->setupUi(this);
    connect(ui->lineEdit_name, &QLineEdit::textChanged, this, &ClassInfoWidget::textChanged);
    connect(ui->lineEdit_path, &QLineEdit::textChanged, this, &ClassInfoWidget::textChanged);

    initStyle();
}

ClassInfoWidget::~ClassInfoWidget()
{
    delete ui;
}

Class ClassInfoWidget::info()
{
    return m_info;
}

void ClassInfoWidget::on_pushButton_browse_clicked()
{
    QString m_imagePath = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Images (*.jpg)"));

    ui->lineEdit_path->setText(m_imagePath);
    if(ui->lineEdit_name->text().isEmpty())
    {
        ui->lineEdit_name->setText(QFileInfo(m_imagePath).baseName());
    }
}

void ClassInfoWidget::textChanged()
{
    QFile image = QFile(ui->lineEdit_path->text());
    if(!ui->lineEdit_name->text().isEmpty()
            && image.open(QIODevice::ReadOnly))
    {
        m_info.name = ui->lineEdit_name->text();
        m_info.image = image.readAll();
        emit infoChanged(m_info);
    }
    else
    {
        emit infoChanged(Class());
    }
}

void ClassInfoWidget::initStyle()
{
    ui->pushButton_browse->setStyleSheet(StyleSheet::buttonStyle());
    ui->label_class->setStyleSheet(StyleSheet::labelStyle(1));
    ui->label_image->setStyleSheet(StyleSheet::labelStyle(1));
    this->setStyleSheet(StyleSheet::lineEditStyle());
}
