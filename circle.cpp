#include "circle.h"
#include "math.h"

Circle::Circle(QObject *parent) : Figure(parent)
{

}

Circle::~Circle()
{

}

QRectF Circle::boundingRect() const
{
    return QRectF(-820,-630,1640,1260);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(QColor(0,0,0), 3));
    painter->drawEllipse(-R, -R, 2 * R, 2 * R);

    painter->setPen(QPen(QColor(16,16,16),3));
    painter->setBrush(QBrush(QColor(107, 107, 107)));
    painter->drawEllipse(pointCenter.x() - 6, pointCenter.y() - 6, 12, 12);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}
