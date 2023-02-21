#include "spinbox.h"
#include "ui_spinbox.h"
class SpinBoxP
{
public:
    SpinBoxP(bool doubleSpin = false)
        :m_doubleSpin(doubleSpin)
    {
        if(m_doubleSpin)
        {
            m_dSpinBox = new QDoubleSpinBox();
            m_dSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        }
        else
        {
            m_spinBox = new QSpinBox();
            m_spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        }
    }
    QSpinBox *spinBox()
    {
        return m_spinBox;
    }
    QDoubleSpinBox *doubleSpinBox()
    {
        return m_dSpinBox;
    }
    void reSetValue()
    {
        if(m_doubleSpin)
        {
            m_dSpinBox->setValue(0);
        }
        else
        {
            m_spinBox->setValue(0);
        }
    }
    bool isDoubleSpin()
    {
        return m_doubleSpin;
    }
private:
    QSpinBox *m_spinBox;
    QDoubleSpinBox *m_dSpinBox;
    bool m_doubleSpin;
};

SpinBox::SpinBox(QWidget *parent, bool doubleSpin) :
    QWidget(parent),
    ui(new Ui::SpinBox),
    p(new SpinBoxP(doubleSpin))
{
    ui->setupUi(this);
    if(doubleSpin)
    {
        ui->horizontalLayout->insertWidget(1,p->doubleSpinBox());
        connect(ui->pushButton_add, &QPushButton::clicked, this, [this]{
            p->doubleSpinBox()->setValue(p->doubleSpinBox()->value()+1);
        });
        connect(ui->pushButton_reduce, &QPushButton::clicked, this, [this]{
            p->doubleSpinBox()->setValue(p->doubleSpinBox()->value()-1);
        });
        connect(p->doubleSpinBox(),static_cast<void (QDoubleSpinBox::*)(double num)>(&QDoubleSpinBox::valueChanged),
                this, static_cast<void (SpinBox::*)(double num)>(&SpinBox::valueChange));
    }
    else
    {
        ui->horizontalLayout->insertWidget(1,p->spinBox());
        connect(ui->pushButton_add, &QPushButton::clicked, this, [this]{
            p->spinBox()->setValue(p->spinBox()->value()+1);
        });
        connect(ui->pushButton_reduce, &QPushButton::clicked, this, [this]{
            p->spinBox()->setValue(p->spinBox()->value()-1);
        });
        connect(p->spinBox(),static_cast<void (QSpinBox::*)(int num)>(&QSpinBox::valueChanged),
                this, static_cast<void (SpinBox::*)(int num)>(&SpinBox::valueChange));
    }
}

SpinBox::~SpinBox()
{
    delete ui;
}

void SpinBox::reSetValue()
{
    p->reSetValue();
}
