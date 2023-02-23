#ifndef CLASSINFOWIDGET_H
#define CLASSINFOWIDGET_H

#include <QWidget>
#include <QMap>
namespace Ui {
class ClassInfoWidget;
}

class ClassInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClassInfoWidget(QWidget *parent = nullptr);
    ~ClassInfoWidget();
    QMap<QString, QByteArray> info();
signals:
    void infoChanged(QMap<QString, QByteArray>);

private slots:
    void on_pushButton_browse_clicked();
    void textChanged();

private:
    void initStyle();
    Ui::ClassInfoWidget *ui;
    QMap<QString, QByteArray> m_info;
};

#endif // CLASSINFOWIDGET_H
