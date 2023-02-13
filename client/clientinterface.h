#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <QWidget>

namespace Ui {
class ClientInterface;
}

class ClientInterface : public QWidget
{
    Q_OBJECT

public:
    explicit ClientInterface(QWidget *parent = nullptr);
    ~ClientInterface();

private:
    Ui::ClientInterface *ui;
};

#endif // CLIENTINTERFACE_H
