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

private:
    Ui::OrderConfirmatDialog *ui;
};

#endif // ORDERCONFIRMATDIALOG_H
