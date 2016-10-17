#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

using namespace ogdf;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{



    cvrand.state = cv::getTickCount();
    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);




    d_newTree = new DialogNewTree(this);

    connect(d_newTree,SIGNAL(accepted()),this,SLOT(apply_newTree()));
    scene = new GraphicsScene();

    scene->setBackgroundBrush(QBrush(Qt::white));

    ui->graphicsView->setScene(scene);

    //tree.generateRandomTree(20);
    scene->create(tree);
    tree.save("test");

    //tree.loadImageList("inputFile.txt");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newTreeButton_clicked()
{
    d_newTree->show();
}

void MainWindow::on_Run_clicked()
{
    tree.execute();
}

void MainWindow::on_actionLoad_Input_File_triggered()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Open Database Input File"),QDir::homePath());

    tree.loadImageList(file,ui->apendText->text());

    qDebug() << "testeFileload";
}

//create Children for node and return the leaf
void MainWindow::createBrothers(AugmentationNode *node, QList<Dialog_Parameters::DialogData> nodeTypes, QList<AugmentationNode *> &leafNodes){

    LayerData currentLayer = d_newTree->layers.at(nodeTypes.first().layerIndex);
    int numBros = cvrand.uniform(currentLayer.brothersMin,currentLayer.brothersMax+1);


    int rnd;
    int h = node->height;
    int b = node->brothers;

    //qDebug()<< currentLayer.brothersMin << currentLayer.brothersMax << currentLayer.hMin << currentLayer.hMax;

    for(int i = 0; i< numBros; i++){

        //instantiate a brother
        node->brothers++;
        rnd =cvrand.uniform(0,nodeTypes.size());
        AugmentationNode *newNode = tree.instantiateNode(nodeTypes[rnd].nodeName);

        //add parameters to the new created node
        qDebug() << nodeTypes[rnd].parameters.size();
        foreach(AugmentationNode::Parameter p, nodeTypes[rnd].parameters){
            qDebug() << p.name;
            newNode->setParameter(p.name,p.value,p.type,p.min,p.max,p.sigma);
        }
        QList<Dialog_Parameters::DialogData> updatedNodeType = nodeTypes;
        updatedNodeType.removeAt(rnd);

        newNode->height = h+1;
        tree.addNode(node,newNode);

        //less than minimum, need to add
        if(h+1 < currentLayer.hMin){
            createBrothers(newNode,updatedNodeType, leafNodes);

        }else{

            if(newNode->brothers < currentLayer.brothersMin)
                rnd = 1;
            else
                rnd = cvrand.uniform(0,2);

            if(rnd == 1 && h+1 < (currentLayer.hMax + currentLayer.priority)){
                createBrothers(newNode, updatedNodeType, leafNodes);
            }else{
                leafNodes << newNode;
            }}
    }
}
void MainWindow::apply_newTree()
{

    //clean the scene
    tree.clear();
    scene->clear();
    scene->setSceneRect(0,0,0,0);

    //get new tree dialog data
    QMap<int,Dialog_Parameters::DialogData> checkedNodes = d_newTree->getDialogData();
    QList<int> priorities = checkedNodes.uniqueKeys();
    qSort(priorities.begin(),priorities.end());
    QList<AugmentationNode*> currentNodes, nextNodes;
    nextNodes << tree.getRoot();

    //construct tree layers
    foreach(int priority, priorities){

        currentNodes = nextNodes;
        nextNodes.clear();

        QList<Dialog_Parameters::DialogData> camada = checkedNodes.values(priority);

        //check for error
        if(camada.size() < d_newTree->layers.at(camada.first().layerIndex).hMax){
            ui->statusBar->showMessage("Error : maximum height must be equal or less than number of selected nodes",4000);
            qDebug() << "Error : maximum height < selected nodes";
            return;
        }

        //create this layer
        foreach(AugmentationNode* insertionNode, currentNodes){

            createBrothers(insertionNode, camada,nextNodes);
        }
    }

    //scene->update(area);
    scene->create(tree);
}

//save a new tree
void MainWindow::on_saveTreeButton_clicked()
{
    QString file = QFileDialog::getSaveFileName(this,tr("Save Tree"),QDir::homePath(),tr("Augmentation Tree (*.bmt)"));
    tree.save(file);
}

//load a new tree
void MainWindow::on_loadTreeButton_clicked()
{
    tree.clear();
    QString file = QFileDialog::getOpenFileName(this,tr("Save Tree"),QDir::homePath(),tr("Augmentation Tree (*.bmt, *.xml)"));
    tree.load(file);
    scene->create(tree);
}
