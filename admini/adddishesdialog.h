#ifndef ADDDISHESDIALOG_H
#define ADDDISHESDIALOG_H

#include <QDialog>

namespace Ui {
class AddDishesDialog;
}

class AddDishesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDishesDialog(QWidget *parent = nullptr);
    ~AddDishesDialog();
    QMap <QString, QByteArray> getInfo();

private slots:
    void on_pushButton_browse_clicked();
    void pathChanged_slot();
    void nameChanged_slot();

private:
    Ui::AddDishesDialog *ui;
    QPushButton * m_okButton;
    QByteArray m_imageData;
    QString m_imagePath;
    bool m_haveName;
    bool m_havePath;
};

#endif // ADDDISHESDIALOG_H
