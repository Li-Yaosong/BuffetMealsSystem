#ifndef ADMINISTRATORINTERFACE_H
#define ADMINISTRATORINTERFACE_H

#include "connectservice.h"
#include <QWidget>

namespace Ui {
class AdministratorInterface;
}

class AdministratorInterface : public QWidget
{
    Q_OBJECT

public:
    explicit AdministratorInterface(QWidget *parent = nullptr);
    ~AdministratorInterface();

private slots:
    void on_noFinished_pushButton_clicked();

    void on_pushButton_addDishes_clicked();

private:
    Ui::AdministratorInterface *ui;
    ConnectService *m_service;
    int m_number;
};

#endif // ADMINISTRATORINTERFACE_H
