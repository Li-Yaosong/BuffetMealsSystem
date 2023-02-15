#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <QWidget>

namespace Ui {
class ClientInterface;
}
class ConnectService;
class CDishWidget;
class ClientInterface : public QWidget
{
    Q_OBJECT

public:
    explicit ClientInterface(QWidget *parent = nullptr);
    ~ClientInterface();
    void updateDishesList();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ClientInterface *ui;
    ConnectService *m_service;
    QList<CDishWidget *> m_dishWidgetList;
};

#endif // CLIENTINTERFACE_H
