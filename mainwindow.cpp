#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1200, 800);

    setScene();
    setFigures();

    ui->radioButtonCircle->setChecked(true);
    ui->spinBox->setEnabled(false);
    isCircle = true;
    applyChanges();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setScene()
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-ui->graphicsView->width()/2, -ui->graphicsView->height()/2,
                        ui->graphicsView->width(), ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->verticalScrollBar()->setEnabled(false);
    ui->graphicsView->horizontalScrollBar()->setEnabled(false);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void MainWindow::setFigures()
{
    circle = new Circle();
    circle->setCenter({0,0});
    circle->setFlags();

    polygon = new Polygon();
    polygon->setCenter({0,0});
    polygon->setFlags();

    figure = new Figure();
    figure->setCenter({0,0});
    figure->setFlags();
    figure->paintMode = false;

    connect(polygon, SIGNAL(signalChanges()),this, SLOT(applyChanges()));
    connect(circle, SIGNAL(signalChanges()),this, SLOT(applyChanges()));
    connect(figure, SIGNAL(signalChanges()),this, SLOT(applyChanges()));
}

void MainWindow::reset()
{
    circle->~Circle();
    polygon->~Polygon();
    figure->~Figure();

    setFigures();

    if (zoomLevel > 0)
    {
        while (zoomLevel != 0)
            zoomOut();
    }
    else
    if (zoomLevel < 0)
    {
        while (zoomLevel != 0)
            zoomIn();
    }

    ui->labelPerimeter->setText("Permiter: - mm");
    ui->labelArea->setText("Square: - sq.mm");
    ui->horizontalSliderRotation->setValue(0);
    ui->horizontalSliderSize->setValue(6);
}

// ---------------------------------------------------------------------------------------------- Изменение параметров
void MainWindow::setPerimeter()
{
    if (isCircle)
        ui->labelPerimeter->setText("Perimeter: " + (QString::number(circle->getPerimeter()))  + " mm");
    else
        ui->labelPerimeter->setText("Perimeter: " + (QString::number(polygon->getPerimeter()))  + " mm");
}

void MainWindow::setArea()
{
    if (isCircle)
        ui->labelArea->setText("Square: " + QString::number(circle->getArea())  + " sq.mm");
    else
        ui->labelArea->setText("Square: " + QString::number(polygon->getArea())  + " sq.mm");
}

void MainWindow::on_horizontalSliderRotation_valueChanged(int value)
{
    ui->labelRotation->setText("Rotation: " + QString::number(value) + "'");
    if (!figure->paintMode)
    {
        if (isCircle)
            circle->rotation(value);
        else
            polygon->rotation(value);
    }
    else
        figure->rotation(value);

}

void MainWindow::on_horizontalSliderSize_valueChanged(int value)
{
    if (!figure->paintMode)
        ui->labelSize->setText("Radius: " + QString::number(value/6) + " mm");
    else
        ui->labelSize->setText("Scale: " + QString::number((double)value/6/0.3) + " %");
    applyChanges();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    applyChanges();
}

// ---------------------------------------------------------------------------------------------- Выбор фигуры
void MainWindow::on_radioButtonCircle_pressed()
{
    reset();
    isCircle = true;

    ui->spinBox->setMinimum(0);
    ui->spinBox->setValue(0);
    ui->spinBox->setEnabled(false);
    ui->horizontalSliderSize->setValue(6);
    ui->horizontalSliderSize->setEnabled(true);
    ui->horizontalSliderRotation->setEnabled(true);
    applyChanges();
}

void MainWindow::on_radioButtonTriangle_pressed()
{
    reset();
    isCircle = false;

    ui->spinBox->setValue(3);
    ui->spinBox->setEnabled(false);
    ui->horizontalSliderSize->setValue(6);
    ui->horizontalSliderSize->setEnabled(true);
    ui->horizontalSliderRotation->setEnabled(true);
    applyChanges();
}

void MainWindow::on_radioButtonSquare_pressed()
{
    reset();
    isCircle = false;

    ui->spinBox->setValue(4);
    ui->spinBox->setEnabled(false);
    ui->horizontalSliderSize->setValue(6);
    ui->horizontalSliderSize->setEnabled(true);
    ui->horizontalSliderRotation->setEnabled(true);
    applyChanges();
}

void MainWindow::on_radioButtonPolygon_pressed()
{
    reset();
    isCircle = false;

    ui->spinBox->setValue(3);
    ui->spinBox->setEnabled(true);
    ui->spinBox->setMinimum(3);
    ui->horizontalSliderSize->setValue(6);
    ui->horizontalSliderSize->setEnabled(true);
    ui->horizontalSliderRotation->setEnabled(true);
    applyChanges();
}

void MainWindow::on_radioButtonFigure_pressed()
{
    reset();
    isCircle = false;

    figure->paintMode = true;
    figure->paintDone = false;

    ui->spinBox->setValue(0);
    ui->spinBox->setEnabled(false);
    ui->horizontalSliderSize->setValue(180); //середина - 100%
    ui->horizontalSliderSize->setEnabled(false);
    ui->horizontalSliderRotation->setEnabled(false);
    applyChanges();
}

// ---------------------------------------------------------------------------------------------- Внесение изменений
void MainWindow::applyChanges()
{
    scene->removeItem(circle);
    scene->removeItem(polygon);
    scene->removeItem(figure);

    int n = ui->spinBox->value();
    int R = ui->horizontalSliderSize->value();

    if (!figure->paintMode)
    {
        if (isCircle)
        {
            circle->changeSize(n, R);
            scene->addItem(circle);
        }
        else
        {
            polygon->changeSize(n, R);
            scene->addItem(polygon);
        }

        setPerimeter();
        setArea();
    }
    else
    {
        if (figure->paintDone)
        {
            ui->horizontalSliderRotation->setEnabled(true);
            ui->horizontalSliderSize->setEnabled(true);
        }
        figure->changeSize(n, R/6);
        scene->addItem(figure);
    }
}


// ---------------------------------------------------------------------------------------------- Масштабирование
void MainWindow::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0)
        setScale(true);
    else
        setScale(false);
}

void MainWindow::setScale(bool zoom)
{
    if (zoom)
    {
        for(int i = 0; i < 10; i++)
            QTimer::singleShot(i * 50, this, SLOT(zoomIn()));
    }
    else
    {
        for(int i = 0; i < 10; i++)
            QTimer::singleShot(i * 50, this, SLOT(zoomOut()));
    }
}

void MainWindow::zoomIn()
{
    if (zoomLevel < 25)
    {
        zoomLevel += zoomFactor;
        ui->graphicsView->scale(zoomFactor, zoomFactor);
    }
}

void MainWindow::zoomOut()
{
    if (zoomLevel > -5)
    {
        zoomLevel -= zoomFactor;
        ui->graphicsView->scale(1.0/zoomFactor, 1.0/zoomFactor);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->XPos->text().isEmpty() || ui->YPos->text().isEmpty()){
        return;
    }
    else{
        QString XValue = ui->XPos->text();
        QString YValue = ui->YPos->text();

        QPoint newPos{XValue.toInt(),YValue.toInt()};

        circle->setPos(newPos);
        polygon->setPos(newPos);
        figure->setPos(newPos);
    }
}
