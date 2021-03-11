#ifndef CIRCLE_H
#define CIRCLE_H

#include <figure.h>

class Circle: public Figure
{
public:
    explicit Circle(QObject *parent = nullptr);
    ~Circle();

private:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // CIRCLE_H
