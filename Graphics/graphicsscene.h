#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H
#include <QGraphicsScene>
#include "augmentationtree.h"
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/tree/TreeLayout.h>
#include <QGraphicsTextItem>
#include <Graphics/graphicnode.h>
#include <Graphics/graphicedge.h>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMap>

using namespace ogdf;
class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene();

    void create(AugmentationTree &tree);

public slots:
    void changedSlot(const QList<QRectF> &region);

private:

    void addGraphicNode(node &n, GraphAttributes &attribute);
    void addGraphicEdge(edge &e, GraphAttributes &attribute);

    QMap<node, GraphicNode*> graphicMap;
};

#endif // GRAPHICSSCENE_H
