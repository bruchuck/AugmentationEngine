#ifndef GRAPHICEDGE_H
#define GRAPHICEDGE_H
#include <QGraphicsLineItem>
#include <Graphics/graphicnode.h>
#include <QGraphicsSceneEvent>
#include <QPen>

class GraphicEdge : public QGraphicsLineItem
{

public:
    GraphicEdge(GraphicNode* in, GraphicNode* out);

    GraphicNode *in, *out;

    void updatePosition();


};

#endif // GRAPHICEDGE_H
