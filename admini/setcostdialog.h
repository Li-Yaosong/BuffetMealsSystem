#ifndef SETCOSTDIALOG_H
#define SETCOSTDIALOG_H

#include <QDialog>

namespace Ui {
class SetCostDialog;
}

class SetCostDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetCostDialog(QWidget *parent = nullptr);
    ~SetCostDialog();
    QPair<QString, double> getInfo();


private:
    Ui::SetCostDialog *ui;
};

#endif // SETCOSTDIALOG_H
