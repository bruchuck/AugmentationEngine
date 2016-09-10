#ifndef AUGMENTATIONTREE_H
#define AUGMENTATIONTREE_H
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/tree/TreeLayout.h>
#include "augmentationnode.h"
#include "logmanager.h"
#include "defenums.h"
#include "Nodes/affineRotation.h"
#include "Nodes/flipimage.h"
#include "Nodes/translation.h"
#include "Nodes/scaleimage.h"
#include "Nodes/blurimage.h"
#include "Nodes/brightnessimage.h"
#include "Nodes/contrastimage.h"
#include "Nodes/noiseimage.h"
#include "Nodes/warpimage.h"


#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QMap>
#include <QDebug>
#include <QDate>
#include <QString>
#include <QStringList>
#include <QDir>

using namespace ogdf;




class AugmentationTree
{
public:

    enum NodeType{
        NONE,
        AFFINE_ROTATION
    };

    AugmentationTree();
    ~AugmentationTree();


    static QList<AugmentationNode::Parameter> getParametersInterface(QString NodeName);
    AugmentationNode* instantiateNode(QString name);

    QMap<node, AugmentationNode*> map;

    void loadImageList(QString name, QString appendURL);
    Mat* loadimage(inputType input);

    //add a Node of type and return it;
    void addNode(AugmentationNode* insertionPoint, AugmentationNode* newNode);

    void execute();

    void layoutTree();

    void generateRandomTree(int n);

    void save(QString fileName);
    void load(QString fileName);

    void clear();

    QList<node> getNodes();
    QList<edge> getEdges();
    GraphAttributes getAttributes();

    AugmentationNode* getRoot();

    node root;

private:

    Graph G;
    GraphAttributes GA;
    int numNodes = 0;

    LogManager* logger;

    QList<inputType> inputList;

};

#endif // AUGMENTATIONTREE_H
