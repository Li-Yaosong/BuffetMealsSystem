#ifndef SELECTCLASSDIALOG_H
#define SELECTCLASSDIALOG_H

#include <QDialog>

namespace Ui {
class SelectClassDialog;
}

class SelectClassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectClassDialog(const QStringList classList, QWidget *parent = nullptr);
    ~SelectClassDialog();
    QString className() const;

private:
    Ui::SelectClassDialog *ui;
};

#endif // SELECTCLASSDIALOG_H
