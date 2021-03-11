#ifndef POLYGON_H
#define POLYGON_H

#include <figure.h>

class Polygon: public Figure
{
public:
    explicit Polygon(QObject *parent = nullptr);
    ~Polygon();

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // POLYGON_H
