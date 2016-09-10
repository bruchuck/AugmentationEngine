#include "graphicedge.h"

GraphicEdge::GraphicEdge(GraphicNode *in, GraphicNode *out):
    QGraphicsLineItem(in->x() + in->rect().width()/2,in->y()+ in->rect().height()/2,out->x() + out->rect().width()/2,out->y() + out->rect().height()/2)
{
    this->in = in;
    this->out = out;
    QPen* pen = new QPen();
    pen->setWidth(2);
    this->setPen(*pen);
}

void GraphicEdge::updatePosition()
{
    setLine(in->x() + in->rect().width()/2,in->y()+ in->rect().height()/2,out->x() + out->rect().width()/2,out->y() + out->rect().height()/2);

}
