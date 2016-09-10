#ifndef GRAPHICNODE_H
#define GRAPHICNODE_H
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QDebug>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>

using namespace ogdf;

class GraphicNode : public QGraphicsRectItem
{

public:
    GraphicNode(node &n, GraphAttributes &attribute);


protected:

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRAPHICNODE_H
