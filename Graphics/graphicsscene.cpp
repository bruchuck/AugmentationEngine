#include "graphicsscene.h"

GraphicsScene::GraphicsScene()
{

    connect(this,SIGNAL(changed(QList<QRectF>)),this,SLOT(changedSlot(const QList<QRectF>&)));

    }

//create the graphical tree
void GraphicsScene::create(AugmentationTree &tree)
{

    this->clear();
    tree.layoutTree();
    QList<node> nodes = tree.getNodes();
    QList<edge> edges = tree.getEdges();
    GraphAttributes GA = tree.getAttributes();

    foreach(node n, nodes){
        addGraphicNode(n,GA);
    }
    foreach(edge e, edges){
        addGraphicEdge(e,GA);
    }
}

void GraphicsScene::changedSlot(const QList<QRectF> &region)
{

    foreach(QRectF sceneRectangle, region){

        QList<QGraphicsItem *>  changedList = items(sceneRectangle);

        foreach(QGraphicsItem* changedItem, changedList){

            GraphicEdge* edge = dynamic_cast<GraphicEdge*>(changedItem);
            if(edge)
                edge->updatePosition();
        }
    }
}


//add node of the tree with the associated graph atribute
void GraphicsScene::addGraphicNode(node &n, GraphAttributes &attribute)
{
    GraphicNode* gNode = new GraphicNode(n, attribute);

    gNode->setBrush(QBrush(Qt::lightGray));
    QGraphicsTextItem* label = new QGraphicsTextItem(attribute.label(n).data(), gNode);
    addItem(gNode);

    graphicMap.insert(n,gNode);
}


void GraphicsScene::addGraphicEdge(edge &e, GraphAttributes &attribute)
{
    GraphicEdge *gEdge = new GraphicEdge(graphicMap.value(e->source()),graphicMap.value(e->target()));
    addItem(gEdge);
}
