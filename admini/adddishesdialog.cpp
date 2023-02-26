#include "adddishesdialog.h"
#include "ui_adddishesdialog.h"
#include <QFileDialog>
#include <QPushButton>
#include "titalwidget.h"
#include "stylesheet.h"
AddDishesDialog::AddDishesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDishesDialog)
{
    ui->setupUi(this);
    m_infoWidget = new DishInfoWidget;
    m_okButton = ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok);
    m_okButton->setText(QString::fromLocal8Bit("确定"));
    m_cancelButton = ui->buttonBox->button(QDialogButtonBox::StandardButton::Cancel);
    m_cancelButton->setText(QString::fromLocal8Bit("取消"));
    connect(m_infoWidget, &DishInfoWidget::infoChanged, this, &AddDishesDialog::dishInfo);
    ui->verticalLayout->insertWidget(0, m_infoWidget);
    TitalWidget *tital = new TitalWidget(this, QString::fromLocal8Bit("添加菜单"),0);
    m_okButton->setStyleSheet(StyleSheet::buttonStyle());
    m_cancelButton->setStyleSheet(StyleSheet::buttonStyle());
    ui->verticalLayout->insertWidget(0,tital);
    m_okButton->setEnabled(false);
}

AddDishesDialog::~AddDishesDialog()
{
    delete ui;
}

QMap<QString, QByteArray> AddDishesDialog::getInfo()
{
    return m_dishInfo;
}

void AddDishesDialog::dishInfo()
{
   DishInfoWidget::DishInfo info = m_infoWidget->info();
   QFile* file=new QFile(info.imagePath); //file为二进制数据文件名
   if(!info.name.isEmpty() && file->open(QIODevice::ReadOnly))
   {
        m_dishInfo.insert("name",info.name.toUtf8());
        m_dishInfo.insert("price",QString::number(info.price).toUtf8());
        m_dishInfo.insert("image",file->readAll());
        m_dishInfo.insert("storage",info.storage.toUtf8());
        m_okButton->setEnabled(true);
   }
   else
   {
       m_okButton->setEnabled(false);
   }
   file->close();
}
