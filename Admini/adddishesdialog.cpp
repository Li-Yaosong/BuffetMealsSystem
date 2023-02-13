#include "adddishesdialog.h"
#include "ui_adddishesdialog.h"
#include <QFileDialog>
AddDishesDialog::AddDishesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDishesDialog)
{
    ui->setupUi(this);
    m_okButton = ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok);
    connect(ui->lineEdit_path,&QLineEdit::textChanged,this,&AddDishesDialog::pathChanged_slot);
    connect(ui->lineEdit_name,&QLineEdit::textChanged,this,&AddDishesDialog::nameChanged_slot);
    m_okButton->setEnabled(false);
}

AddDishesDialog::~AddDishesDialog()
{
    delete ui;
}

QMap<QString, QByteArray> AddDishesDialog::getInfo()
{
    QMap<QString, QByteArray> map;
    map.insert("name",ui->lineEdit_name->text().toUtf8());
    map.insert("price",ui->doubleSpinBox_price->text().toUtf8());
    map.insert("image",m_imageData);
    map.insert("storage","yes");
    return map;
}

void AddDishesDialog::on_pushButton_browse_clicked()
{
    QString m_imagePath = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Images (*.jpg)"));
    ui->lineEdit_path->setText(m_imagePath);
}

void AddDishesDialog::pathChanged_slot()
{
    QFile* file=new QFile(ui->lineEdit_path->text()); //file为二进制数据文件名
    if(file->open(QIODevice::ReadOnly))
    {
        m_imageData = file->readAll();
        m_havePath = true;
        file->close();
    }
    if(m_haveName && m_havePath)
    {
        m_okButton->setEnabled(true);
    }
}

void AddDishesDialog::nameChanged_slot()
{
    if(!ui->lineEdit_name->text().isEmpty())
    {
        m_haveName = true;
    }
    if(m_haveName && m_havePath)
    {
        m_okButton->setEnabled(true);
    }

}

