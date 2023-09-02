//
// Created by konstantin on 21.05.23.
//

#include "canvas.h"
#include <QMouseEvent>
#include <QList>
//#include "Figures/Circle.h"
Canvas::Canvas(Settings& settings,QObject *widget) : QGraphicsScene(widget), settings(settings) {
    drawMode = DrawMode::No;
    prevItem = nullptr;
    pressedLMB = false;
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QPen pen(settings.color,settings.width);
    if (pressedLMB) {
        if (drawMode == DrawMode::Pen) {
            paths.push_back(std::pair(new QPainterPath,pen));
            figures.push_back(addLine(prevPoint.x(), prevPoint.y(), event->scenePos().x(), event->scenePos().y(), pen));
            paths.back().first->addPath(figures.back()->shape());
            prevPoint = event->scenePos();
        }
        if (drawMode == DrawMode::Line) {
            delete prevItem;
            prevItem = addLine(prevPoint.x(), prevPoint.y(), event->scenePos().x(), event->scenePos().y(), pen);
        }
    }
}

void Canvas::setDrawMode(Canvas::DrawMode mode) {
    drawMode = mode;
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event) {

    QGraphicsScene::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        pressedLMB = true;
        QPen pen(settings.color,settings.width);
        if (drawMode == DrawMode::Pen) {
            figures.push_back(addLine(event->scenePos().x(), event->scenePos().y(), event->scenePos().x(), event->scenePos().y(), pen));
            paths.push_back(std::pair(new QPainterPath,pen));
            paths.back().first->addPath(figures.back()->shape());
            //paths.back()->addLine(event->scenePos().x(), event->scenePos().y(), event->scenePos().x(), event->scenePos().y(), pen));
        }
        if (drawMode == DrawMode::Rect) {

            int h = settings.RectangleWidth;
            int w = settings.RectangleHeight;
            //paths.push_back(new QPainterPath);
            paths.push_back(std::pair(new QPainterPath,pen));
            figures.push_back(addRect(event->scenePos().x() - w / 2., event->scenePos().y() - h / 2., w, h, pen));
            //paths.back()->addRect(event->scenePos().x() - w / 2., event->scenePos().y() - h / 2., w, h);
            paths.back().first->addPath(figures.back()->shape());

            // figures.push_back(addRect(event->scenePos().x() - w / 2., event->scenePos().y() - h / 2., w, h, pen));
            //            figures.back()->setAcceptedMouseButtons(Qt::MouseButtons::)
            //figures += this->items(*paths.back());
        }
        if (drawMode == DrawMode::Circle) {
            int R = settings.CircleRadius;
            paths.push_back(std::pair(new QPainterPath,pen));
            paths.back().first->addEllipse(event->scenePos().x() - R / 2., event->scenePos().y() - R / 2., R, R);
            figures.push_back(this->addEllipse(event->scenePos().x() - R / 2., event->scenePos().y() - R / 2., R, R,pen));
        }
        prevPoint = event->scenePos();
    }

}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
    QPen pen(settings.color,settings.width);
    if (event->button() == Qt::LeftButton) {
        if (drawMode == DrawMode::Line) {
            figures.push_back(prevItem);
            paths.push_back(std::pair(new QPainterPath,pen));
            paths.back().first->addPath(figures.back()->shape());
            prevItem = nullptr;
        }
        if (drawMode == DrawMode::Pen) {
            if (drawMode == DrawMode::Pen) {
                figures.push_back(addLine(event->scenePos().x(), event->scenePos().y(), event->scenePos().x(), event->scenePos().y(), pen));
                paths.push_back(std::pair(new QPainterPath,pen));
                paths.back().first->addPath(figures.back()->shape());
            }
        }
    }
    pressedLMB = false;
}

//QList<QGraphicsItem*> &Canvas::getFigures() {
//    return figures;
//}


