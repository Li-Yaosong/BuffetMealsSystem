#ifndef ORDERCONFIRMATDIALOG_H
#define ORDERCONFIRMATDIALOG_H

#include <QDialog>

namespace Ui {
class OrderConfirmatDialog;
}

class OrderConfirmatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OrderConfirmatDialog(QMap<QString, int> map, QWidget *parent = nullptr);
    ~OrderConfirmatDialog();
    void setButtonText(QString ok = QStringLiteral("确定"), QString cancel = QStringLiteral("取消"));

private:
    Ui::OrderConfirmatDialog *ui;
};

#endif // ORDERCONFIRMATDIALOG_H
