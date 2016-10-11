#include "augmentationtree.h"

AugmentationTree::AugmentationTree()
{

    GA.init(G, GraphAttributes::nodeGraphics | GraphAttributes::edgeGraphics | GraphAttributes::nodeLabel | GraphAttributes::nodeId);

    root = G.newNode();
    GA.label(root) = "root";
    GA.width(root) = GRAPHICWIDTH;
    AugmentationNode* aroot = new AugmentationNode();
    map.insert(root,aroot);
    numNodes++;
    logger = new LogManager("log"+ QDate::currentDate().toString(Qt::ISODate) +".xml");
}

AugmentationTree::~AugmentationTree()
{

}


//for each augmentation node you node to call the parameters interface
QList<AugmentationNode::Parameter> AugmentationTree::getParametersInterface(QString nodeName)
{

    if(nodeName == "Rotation"){
        return AffineRotation::parametersInterface();
    }else if(nodeName == "Translation"){
        return Translation::parametersInterface();
    }else if(nodeName == "Scale"){
        return ScaleImage::parametersInterface();
    }else if(nodeName == "Blur"){
        return BlurImage::parametersInterface();
    }else if(nodeName == "Noise"){
        return NoiseImage::parametersInterface();
    }else if(nodeName == "Warp"){
        return WarpImage::parametersInterface();
    }else if(nodeName == "Flip"){
        return FlipImage::parametersInterface();
    }else if(nodeName == "Brightness"){
        return BrightnessImage::parametersInterface();
    }else if(nodeName == "Contrast"){
        return ContrastImage::parametersInterface();
    }else if(nodeName == "PCA"){
        return WarpImage::parametersInterface();
    }else{

        qDebug() << "error, getParametersInterface not implemented for Node type " << nodeName;
        return QList<AugmentationNode::Parameter>();
    }

}

AugmentationNode *AugmentationTree::instantiateNode(QString name)
{

    if(name == "Root"){
        return getRoot();
    }else if(name == "Rotation"){
        return new AffineRotation();
    }else if(name == "Translation"){
        return new Translation();
    }else if(name == "Scale"){
        return new ScaleImage();
    }else if(name == "Flip"){
        return new FlipImage();
    }else if(name == "Blur"){
        return new BlurImage();
    }else if(name == "Noise"){
        return new NoiseImage();
    }else if(name == "Warp"){
        return new WarpImage();
    }else if(name == "Brightness"){
        return new BrightnessImage();
    }else if(name == "Contrast"){
        return new ContrastImage();
    }else if(name == "PCA"){
        return NULL;
    }else{
        qDebug() << "error, no instantiation rule for node of name : " << name;
    }

}

void AugmentationTree::loadImageList(QString name, QString appendURL)
{

    QFile file(name);
    if(!file.open(QIODevice::ReadOnly)){
        //qWarning( "error", file.errorString());
        qDebug() << "error openning input file";
    }

    QTextStream in(&file);

    while(!in.atEnd()) {

        QString line = in.readLine();
        QStringList fields = line.split(" ");
        if(fields.size() == 2){

        QString filePath = fields[0];


        inputType entry;
        entry.path = QDir(filePath);

        if(entry.path.canonicalPath() == ""){
            //qDebug() << "Wrong file path, do you want to append ?";
            entry.path= QDir(filePath.prepend(appendURL));
            //qDebug() << entry.path;

        }

        qDebug() << entry.path.canonicalPath();

        QStringList completePath = entry.path.canonicalPath().split("/");
        QString fileName = completePath.last();
        fileName.chop(4);
        qDebug() << fileName;
        entry.name = fileName;
        entry.classification = fields[1];

        inputList << entry;
        }else{
            qDebug() << "error reading image input, check input file";
        }
    }
}

Mat* AugmentationTree::loadimage(inputType input)
{

    Mat* image = new Mat();
    *image = imread(input.path.absolutePath().toStdString().data());

    if(!image->empty()){
        logger->LogLoadImage(input, true);
        return image;
    }else{
        logger->LogLoadImage(input,false, "failed to load image");
        qDebug() << "error loading image";
        return NULL;
    }
}

void AugmentationTree::addNode( AugmentationNode* insertionPoint,  AugmentationNode* newNode)
{

    node n = G.newNode();

    GA.label(n) = (newNode->getName() + QString::number(n->index())).toStdString();
    GA.width(n) = GRAPHICWIDTH;

    edge e = G.newEdge(map.key(insertionPoint),n);

    newNode->setInputNode(insertionPoint);
    newNode->setIndex(n->index());

    newNode->height = insertionPoint->height + 1;

    map.insert(n,newNode);

    numNodes++;
}

//execute the tree
void AugmentationTree::execute()
{
    QString savePlace = "./results/";
    QList<node> nodes = getNodes();
    logger->startLog();
    int cont = 1, total = inputList.size();

    foreach(inputType entry, inputList){

        qDebug() << "Running image |" << cont << "| of |" << total << "|  : "<< entry.name;
        QList<AugmentationNode*> stack;
        Mat* data = loadimage(entry);
        map[root]->setInputData(data);
        QDir dir(savePlace+entry.classification);

        foreach(node n, nodes){

            map[n]->run();
            logger->LogNode(map[n]);
            map[n]->saveOutputData(entry, dir);

            //Deallocate unecessary data
            if(!stack.isEmpty()){
                if(map[n]->height <= stack.last()->height){
                    int dif = stack.last()->height - map[n]->height;
                    for(int i =0; i<= dif; i++){
                        stack.takeLast()->deallocateOutput();
                    }
                }
            }
            stack << map[n];
        }

        //Deallocate residual data
        for(int i =0; i< stack.size() ; i++){
            stack[i]->deallocateOutput();
        }
        cont++;
    }

    logger->closeLog();
    logger->printErrors();
}

//layout the tree for graphical use
void AugmentationTree::layoutTree()
{
    TreeLayout layout;
    layout.call(GA);
}

//generate a random tree
void AugmentationTree::generateRandomTree(int n)
{

    randomTree(G,n);
    root = G.firstNode();
    QList<node> nodes = getNodes();
    numNodes = 0;

    foreach(node no, nodes){
        AugmentationNode *newNode = new AugmentationNode();
        GA.label(no) = newNode->getName().toStdString();

        map.insert(no,newNode);
        numNodes++;
    }

    GA.setAllWidth(100);
}

/**
 * @brief AugmentationTree::save
 * @param fileName
 */
void AugmentationTree::save(QString fileName)
{

    if(!fileName.endsWith(".xml",Qt::CaseInsensitive))
        fileName.append(".xml");

    QFile saveFile(fileName);

    saveFile.open(QFile::WriteOnly);

    QXmlStreamWriter writer(&saveFile);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("Augmentation_Tree");

    writer.writeAttribute("numNodes",QString::number(numNodes));


    //record all tree parameters
    //record all nodes and parameters

    QList<node> nodeList = getNodes();
    foreach(node n, nodeList){

        writer.writeStartElement("Node");
        writer.writeAttribute("index",QString::number(n->index()));

        writer.writeTextElement("name",map[n]->getName());

        QMap<QString, AugmentationNode::Parameter> nodeParameters = map[n]->getParameters();
        if(!nodeParameters.isEmpty()){
            writer.writeStartElement("Parameters");
            foreach(AugmentationNode::Parameter p, nodeParameters){

                switch(p.type){

                case AugmentationNode::PARAMETER_FIXED:

                    writer.writeStartElement(p.name);
                    writer.writeAttribute("Type","Fixed_Value");

                    if(p.value.canConvert<QString>()){
                        writer.writeTextElement("Value",p.value.toString());
                    }else if(p.value.canConvert<QPointF>()){
                        writer.writeStartElement("QPointF");
                        writer.writeTextElement("x",QString::number(p.value.toPointF().x()));
                        writer.writeTextElement("y",QString::number(p.value.toPointF().y()));
                        writer.writeEndElement();
                    }else{
                        qDebug() << "cant write attribute of type" << p.value.typeName();
                    }

                    writer.writeEndElement();
                    break;
                case AugmentationNode::PARAMETER_UNIFORM:

                    writer.writeStartElement(p.name);
                    writer.writeAttribute("Type", "Uniform_Random");
                    writer.writeTextElement("MinValue",QString::number(p.min));
                    writer.writeTextElement("MaxValue",QString::number(p.max));
                    writer.writeEndElement();
                    break;

                case AugmentationNode::PARAMETER_GAUSSIAN:
                     writer.writeStartElement(p.name);
                     writer.writeAttribute("Type", "Uniform_Gaussian");
                     writer.writeTextElement("Sigma",QString::number(p.sigma));
                     writer.writeEndElement();

                    break;
                }

            }
            writer.writeEndElement();
        }
        writer.writeEndElement();
    }

    QList<edge> edgeList = getEdges();
    foreach(edge e, edgeList){

        writer.writeStartElement("Edge");
        writer.writeAttribute("source",QString::number(e->source()->index()));
        writer.writeAttribute("target",QString::number(e->target()->index()));
        writer.writeEndElement();
    }

    writer.writeEndDocument();
    saveFile.close();

}

void AugmentationTree::load(QString fileName)
{
    QFile loadFile(fileName);

    loadFile.open(QFile::ReadOnly);

    QXmlStreamReader reader(&loadFile);

    QList<AugmentationNode*> nodes;

    while (!reader.atEnd()) {

        reader.readNextStartElement();

        qDebug() << reader.name();

        if(reader.name() == "Node"){

            reader.readNextStartElement();
            QString name = reader.readElementText();
            AugmentationNode *node = instantiateNode(name);
            reader.readNextStartElement();

            qDebug() << reader.name();
            if(reader.name() == "Parameters"){

                reader.readNextStartElement();
                while(reader.name() != "Parameters"){

                    AugmentationNode::Parameter p;
                    p.name = reader.name().toString();

                    QXmlStreamAttribute type = reader.attributes().first();

                    if(type.value().compare("Uniform_Random") == 0){
                        p.type = AugmentationNode::PARAMETER_UNIFORM;
                        reader.readNextStartElement();
                        p.min = reader.readElementText().toDouble();
                        reader.readNextStartElement();
                        p.max = reader.readElementText().toDouble();
                        p.value = 0.0;
                        reader.readNextStartElement();
                        reader.readNextStartElement();
                        qDebug() << p.min << p.max << reader.name();

                        node->setParameter(p);

                    }
                    else if(type.value().compare("Fixed_Value") == 0){
                        p.type = AugmentationNode::PARAMETER_FIXED;
                        reader.readNextStartElement();
                        p.value = reader.readElementText().toDouble();
                        reader.readNextStartElement();
                        reader.readNextStartElement();
                        qDebug() << p.value << reader.name();

                        node->setParameter(p);
                    }
                }
                reader.readNextStartElement();
            }

            nodes << node;
        }
        else if(reader.name() =="Edge"){

            int source = reader.attributes().first().value().toInt();
            int target = reader.attributes().at(1).value().toInt();
            addNode(nodes[source],nodes[target]);

            reader.readNextStartElement();
        }

    }
    if (reader.hasError()) {
        qDebug() << reader.errorString();
      }

    loadFile.close();
}


void AugmentationTree::clear()
{

    G.clear();
    AugmentationNode *node = map[root];
    root = G.newNode();
    GA.label(root) = "root";
    GA.width(root) = GRAPHICWIDTH;
    map.clear();
    map.insert(root,node);
    numNodes = 1;


}

//return a list of all nodes (BFS ordering)
QList<node> AugmentationTree::getNodes()
{
    QList<node> nodes;
    QList<node> search;
    node v;

    search.append(root);
    while(!search.isEmpty()){

        v = search.takeLast();
        nodes.append(v);

        QList<edge> edges;
        G.outEdges(v,edges);

        for(int i=edges.size()-1; i >= 0; i--){
            search.append(edges[i]->target());
        }
    }

    return nodes;
}

//return a list of all Edges
QList<edge> AugmentationTree::getEdges()
{
    QList<edge> edges;
    G.allEdges(edges);
    return edges;
}

//return the graph layout attributes
GraphAttributes AugmentationTree::getAttributes(){
    return GA;
}

AugmentationNode *AugmentationTree::getRoot()
{
    return map[root]; 
}
