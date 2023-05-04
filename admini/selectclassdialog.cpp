#include "selectclassdialog.h"
#include "ui_selectclassdialog.h"
#include "titalwidget.h"
#include <QPushButton>
SelectClassDialog::SelectClassDialog(const QStringList classList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectClassDialog)
{
    ui->setupUi(this);
    TitalWidget *tital = new TitalWidget(this, QStringLiteral("选择要删除的种类"), false);
    ui->verticalLayout->insertWidget(0, tital);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(QStringLiteral("确认"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(QStringLiteral("取消"));
    ui->comboBox->addItems(classList);
}

SelectClassDialog::~SelectClassDialog()
{
    delete ui;
}

QString SelectClassDialog::className() const
{
    return ui->comboBox->currentText();
}
