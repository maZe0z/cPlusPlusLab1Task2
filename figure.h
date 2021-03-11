#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPaintEvent>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QTimer>
#include <math.h>
#define PI 3.14159265359

class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Figure(QObject *parent = 0);
    ~Figure();

    QTimer *timer;

    int n;    //количество углов
    double R; //радиус
    double P; //периметр
    double S; //площадь
    double percent = 1;
    bool paintMode = false;
    bool paintDone = false;

    void setCenter(QPointF newCenter);
    void setFlags();

    void changeSize(int n, int r);
    void rotation(int value);

    double getPerimeter();
    double getArea();

signals:
    void signalChanges();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

protected:
    std::vector<QPointF> points;
    QPointF startPoint;
    QPointF previousPoint;
    QPointF pointCenter;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    void cursorPressed(QGraphicsSceneMouseEvent *event);
    void cursorMoved(QGraphicsSceneMouseEvent *event);
    void cursorReleased(QGraphicsSceneMouseEvent *event);
};

#endif // FIGURE_H
