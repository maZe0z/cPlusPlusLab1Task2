#include "polygon.h"
#include "math.h"

Polygon::Polygon(QObject *parent)  : Figure(parent)
{

}

Polygon::~Polygon()
{

}

QRectF Polygon::boundingRect() const
{
    return QRectF(-820,-630,1640,1260);
}

void Polygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for (int i = 0; i < n; i++)
    {
        double angle = i * 2 * PI / n + PI / n;
        QPointF P = {R * sin(angle), R * cos(angle)};
        points.push_back(P);
    }
    QPolygonF poly;

    for (int i = 0; i < (int)points.size(); i++)
        poly << points[i];

    painter->setPen(QPen(QColor(0,0,0), 3));

    painter->drawPolygon(poly);

    painter->setPen(QPen(QColor(16,16,16), 3));
    painter->setBrush(QBrush(QColor(107, 107, 107)));
    painter->drawEllipse(pointCenter.x() - 6, pointCenter.y() - 6, 12, 12);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}
