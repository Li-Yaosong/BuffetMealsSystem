#ifndef TIPSDIALOG_H
#define TIPSDIALOG_H

#include <QDialog>

namespace Ui {
class TipsDialog;
}

class TipsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TipsDialog(QWidget *parent = nullptr);
    ~TipsDialog();

private:
    Ui::TipsDialog *ui;
};

#endif // TIPSDIALOG_H
