#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QLabel>
#include <QMouseEvent>
#include <QPoint>
#include <QRect>



class ImageWidget : public QLabel
{
    Q_OBJECT
public:
    explicit ImageWidget( QWidget *parent = 0 );
    void setImage( QImage image );
    QImage getFramedImage();

private slots:
    void mousePressEvent( QMouseEvent *e );
    void mouseMoveEvent( QMouseEvent *e );
    void mouseReleaseEvent( QMouseEvent *e );
private:
    bool drawingFrame;
    bool frameDrawn;
    QPoint firstFramePoint;
    QPoint secondFramePoint;
    QRect frame;
    QImage image;

    void paintEvent( QPaintEvent * );
};

#endif // IMAGEWIDGET_H
