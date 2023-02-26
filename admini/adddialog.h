#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QMap>
namespace Ui {
class AddDialog;
}
class AddDialogP;
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
    void setOkButtonState(QMap<QString, QByteArray> info);

private:
    Ui::AddDialog *ui;
    AddDialogP * const p;
};

#endif // ADDDIALOG_H
