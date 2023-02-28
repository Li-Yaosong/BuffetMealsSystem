#ifndef TIPSDIALOG_H
#define TIPSDIALOG_H

#include <QDialog>
#include "libbms_global.h"

namespace Ui {
class TipsDialog;
}

class LIBBMS_EXPORT TipsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TipsDialog(QWidget *parent = nullptr);
    ~TipsDialog();

private:
    Ui::TipsDialog *ui;
};

#endif // TIPSDIALOG_H
