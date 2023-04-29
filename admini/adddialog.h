#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QMap>
#include "common.h"
namespace Ui {
class AddDialog;
}
class AddDialogP;
using namespace Common;
class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();
    void addWidget(QWidget *widget);
    QMap<QString, QByteArray> getInfo();
    QPushButton *okButton();
public slots:
    void dishInfoChanged(Dish dishInfo);
    void classInfoChanged(Class classInfo);
private:
    Ui::AddDialog *ui;
    AddDialogP * const p;
};

#endif // ADDDIALOG_H
