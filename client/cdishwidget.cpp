#include "cdishwidget.h"
#include "ui_cdishwidget.h"
#include "common.h"
#include "imagewidget.h"
CDishWidget::CDishWidget(QWidget *parent, Common::Dish dishIfon) :
    QWidget(parent),
    ui(new Ui::CDishWidget),
    m_dishInfo(dishIfon)
{
    ui->setupUi(this);
    ui->label_name->setText(m_dishInfo.name);
    ui->label_price->setText(QStringLiteral("￥ ")+QString::number(m_dishInfo.price));
    m_image = new ImageWidget(this,m_dishInfo.image);
    m_spinBox = new SpinBox(ui->groupBox);
    ui->verticalLayout->insertWidget(1, m_image);
    creatButton();
    ui->horizontalLayout->insertWidget(3,m_spinBox);
    connect(ui->pushButton_clean, &QPushButton::clicked, this, &CDishWidget::reSetNumber);
    connect(m_spinBox,static_cast<void (QSpinBox::*)(int num)>(&QSpinBox::valueChanged),
            this, &CDishWidget::valueChange);
}

CDishWidget::~CDishWidget()
{
    delete ui;
}

void CDishWidget::creatButton()
{
    QPushButton *button = new QPushButton(m_image);
    button->resize(25, 25);
    button->move(m_image->width() - 40,m_image->height() - 40);
    connect(button, &QPushButton::clicked, this,[this]{
        (new ImageWidget(nullptr, m_dishInfo.image, m_dishInfo.name,600))->show();
    });
}

void CDishWidget::reSetNumber()
{
    m_spinBox->reSetNumber();
}

void CDishWidget::valueChange(int num)
{
    emit dataChange(QPair<QString, int>(ui->label_name->text(), num));
}
