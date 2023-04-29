#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
//#include "libbms_global.h"

namespace Ui {
class ImageWidget;
}

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr, QByteArray data = "",
                         QString title ="", int size = 400);
    ~ImageWidget();
    void updateImage(QByteArray data);

private:
    Ui::ImageWidget *ui;
    QPixmap m_image;
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // IMAGEWIDGET_H
