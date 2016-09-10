#include "graphicnode.h"

GraphicNode::GraphicNode(node &n, GraphAttributes &attribute):
    QGraphicsRectItem(0, 0,attribute.width(n),attribute.height(n))
{

    setPos(attribute.x(n)-rect().width(), attribute.y(n)-rect().height());
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
    setZValue(1);

}

void GraphicNode::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(QBrush(Qt::red));
}

void GraphicNode::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(QBrush(Qt::lightGray));
}

void GraphicNode::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{

}

void GraphicNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setPos(event->scenePos() - rect().bottomRight()/2);

}



