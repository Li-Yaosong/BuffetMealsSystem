#include "titalwidget.h"
#include "stylesheet.h"
#include "ui_titalwidget.h"
#include <QMouseEvent>
TitalWidget::TitalWidget(QWidget *parent, QString tital, bool maxButton)
    :QWidget(parent),
    ui(new Ui::TitalWidget),
    m_parent(parent)
{
    ui->setupUi(this);
    ui->label_tital->setText(tital);
    ui->label_tital->setStyleSheet("font: 25 14pt '微软雅黑 Light';");
    m_parent->setStyleSheet("background-color: rgb(108, 155, 255);");
    m_parent->setWindowFlags(Qt::FramelessWindowHint);
    if(!maxButton)
    {
        ui->pushButton_max->hide();
    }
    ui->pushButton_exit->setStyleSheet(StyleSheet::buttonStyle(2));
    ui->pushButton_max->setStyleSheet(StyleSheet::buttonStyle(3));
    ui->pushButton_min->setStyleSheet(StyleSheet::buttonStyle(4));
}

TitalWidget::~TitalWidget()
{
    delete ui;
}

void TitalWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_Difference = event->globalPos() - m_parent->pos();
    }
}

void TitalWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_parent->move(event->globalPos() - m_Difference);
}


void TitalWidget::on_pushButton_max_clicked()
{
    if(m_parent->isMaximized())
    {
        m_parent->showNormal();
    }
    else
    {
        m_parent->showMaximized();
    }
}


void TitalWidget::on_pushButton_min_clicked()
{
    m_parent->showMinimized();
}


void TitalWidget::on_pushButton_exit_clicked()
{
    m_parent->close();
}

