#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Graphics/graphicsscene.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/tree/TreeLayout.h>
#include <QList>
#include <QDebug>
#include <QRectF>
#include "augmentationtree.h"
#include "augmentationnode.h"

#include "Nodes/affineRotation.h"
#include <QFileDialog>
#include "dialog_newtree.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    AugmentationTree tree;
    ~MainWindow();

private slots:
    void on_newTreeButton_clicked();

    void on_Run_clicked();

    void on_actionLoad_Input_File_triggered();

    void apply_newTree();

    void on_saveTreeButton_clicked();

    void on_loadTreeButton_clicked();

private:
    void createBrothers(AugmentationNode *node, QList<Dialog_Parameters::DialogData> nodeTypes, QList<AugmentationNode*> &leafNodes);
    Ui::MainWindow *ui;
    GraphicsScene *scene;

    DialogNewTree *d_newTree;
};

#endif // MAINWINDOW_H
