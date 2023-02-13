#ifndef ADMINISTRATORINTERFACE_H
#define ADMINISTRATORINTERFACE_H

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

private:
    Ui::AdministratorInterface *ui;
};

#endif // ADMINISTRATORINTERFACE_H
