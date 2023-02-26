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
    m_image = new ImageWidget(ui->widget_image,m_dishInfo.image, "",200);
    m_spinBox = new SpinBox();
    ui->horizontalLayout_4->insertWidget(1, m_image);
    ui->horizontalLayout_2->insertWidget(1,m_spinBox);
    connect(ui->pushButton_clean, &QPushButton::clicked, this, &CDishWidget::reSetNumber);
    connect(m_spinBox,static_cast<void (SpinBox::*)(int num)>(&SpinBox::valueChange),
            this, &CDishWidget::valueChange);
    this->setStyleSheet(StyleSheet::style());
}

CDishWidget::~CDishWidget()
{
    delete ui;
}

void CDishWidget::createBind(CDishWidget *widget)
{
    m_widget = widget;
    connect(widget, &CDishWidget::dataChange, [this](QPair<QString, int> pair)
    {
        if(int(m_spinBox->value()) != pair.second)
        {
            m_spinBox->reSetValue(pair.second);
        }
    });
    connect(this, &CDishWidget::dataChange, [this](QPair<QString, int> pair)
    {
        m_widget->spinBox()->reSetValue(pair.second);
    });
}

SpinBox *CDishWidget::spinBox()
{
    return m_spinBox;
}

void CDishWidget::reSetNumber()
{
    m_spinBox->reSetValue();
}

void CDishWidget::valueChange(int num)
{
    emit dataChange(QPair<QString, int>(ui->label_name->text(), num));
}
