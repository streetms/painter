//
// Created by konstantin on 21.05.23.
//

#ifndef KAZ_BREKKER_CANVAS_H
#define KAZ_BREKKER_CANVAS_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QList>
#include "settings.h"
class Canvas : public  QGraphicsScene{
Q_OBJECT
public:
    explicit Canvas(Settings& settings,QObject* widget = nullptr);
    enum class DrawMode{Pen,Rect,Circle,Line,No};
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void setDrawMode(DrawMode mode);
    //QList<QGraphicsItem*>& getFigures();
//    void resizeEvent(QResizeEvent* event) ;
    QList<QGraphicsItem*> figures;
    QList<std::pair<QPainterPath*,QPen>> paths;
private:
    Settings& settings;
    QPointF prevPoint;
    DrawMode drawMode;
    QGraphicsLineItem* prevItem;


    bool pressedLMB;
};


#endif //KAZ_BREKKER_CANVAS_H
