#ifndef ADDDISHESDIALOG_H
#define ADDDISHESDIALOG_H

#include <QDialog>
#include "dishinfowidget.h"
#include <QMap>
namespace Ui {
class AddDishesDialog;
}

class AddDishesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDishesDialog(QWidget *parent = nullptr);
    ~AddDishesDialog();
    QMap<QString, QByteArray> getInfo();

private slots:
    void dishInfo();

private:
    Ui::AddDishesDialog *ui;
    DishInfoWidget *m_infoWidget;
    QMap<QString, QByteArray> m_dishInfo;
    QPushButton * m_okButton;
};

#endif // ADDDISHESDIALOG_H
