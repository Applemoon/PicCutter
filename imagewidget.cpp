#include "imagewidget.h"
#include <QDebug>
#include <QPainter>



ImageWidget :: ImageWidget( QWidget *parent ) :
    QLabel( parent )
{
    drawingFrame = false;
    frameDrawn = false;
    firstFramePoint = QPoint( -1, -1 );
    secondFramePoint = QPoint( -1, -1 );
}



void ImageWidget :: setImage( QImage vimage )
{
    image = vimage;
    setPixmap( QPixmap::fromImage( vimage ) );
    resize( vimage.size() );
}



QImage ImageWidget :: getFramedImage()
{
    return image.copy( QRect( firstFramePoint, secondFramePoint ) );
}



void ImageWidget :: mousePressEvent( QMouseEvent *e )
{
    if ( e->button() == Qt::LeftButton )
    {
        const int x = e->x();
        const int y = e->y();
        firstFramePoint = QPoint( x, y );
        secondFramePoint = QPoint( -1, -1 );
        drawingFrame = true;
        frameDrawn = false;
    }
}



void ImageWidget :: mouseMoveEvent( QMouseEvent *e )
{
    int x = e->x();
    if ( x < 0 )
        x = 0;
    else if ( x > image.size().width() )
        x = image.size().width() - 2;

    int y = e->y();
    if ( y < 0 )
        y = 0;
    else if ( y > image.size().height() )
        y = image.size().height() - 2;

    secondFramePoint = QPoint( x, y );
    update();
}



void ImageWidget :: mouseReleaseEvent( QMouseEvent *e )
{
    if ( e->button() == Qt::LeftButton )
    {
        int x = e->x();
        if ( x < 0 )
            x = 0;
        else if ( x > image.size().width() )
            x = image.size().width() - 2;

        int y = e->y();
        if ( y < 0 )
            y = 0;
        else if ( y > image.size().height() )
            y = image.size().height() - 2;

        secondFramePoint = QPoint( x, y );
        drawingFrame = false;
        frameDrawn = true;
        update();
    }
}



void ImageWidget :: paintEvent( QPaintEvent * )
{
    QPainter painter;

    painter.begin( this );
    painter.drawImage( 0, 0, image );

    const bool normalFrameSize = ( ( abs( firstFramePoint.rx() - secondFramePoint.rx() ) > 1 )
                                   && ( abs( firstFramePoint.ry() - secondFramePoint.ry() ) > 1 ) );

    if ( drawingFrame || ( frameDrawn && normalFrameSize ) )
    {
        QPen pen;
        pen.setStyle( Qt::DashLine );
        pen.setWidth( 1 );
        pen.setColor( Qt::blue );
        painter.setPen( pen );

        painter.drawRect( QRect( firstFramePoint, secondFramePoint ) );
    }
    painter.end();
}



