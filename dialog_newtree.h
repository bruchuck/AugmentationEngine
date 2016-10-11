#ifndef DIALOGNEWTREE_H
#define DIALOGNEWTREE_H

#include <QDialog>
#include <QComboBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QList>
#include <QMap>

#include "defenums.h"
#include "augmentationtree.h"
#include "dialog_parameters.h"

namespace Ui {
class DialogNewTree;
}

class DialogNewTree : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewTree(QWidget *parent = 0);
    ~DialogNewTree();

    QMap<int, Dialog_Parameters::DialogData> getDialogData();
    QList<LayerData> layers;


private:


    void createNewLayerUI();
    void createDialogDataInterface();
    QMap<QString, Dialog_Parameters::DialogData> dialogDataMap;

private slots:

    void changeParameters_clicked();
    void setNodeParameters();
    void spinBoxChanged(int value);
    void layerChanged(int value);

    void on_newLayerButton_clicked();

    void on_resizeBox_clicked();

    void on_resizeXBox_valueChanged(int arg1);

    void on_resizeYBOX_valueChanged(int arg1);

private:
    Ui::DialogNewTree *ui;

    void createParameterDialog(QList<AugmentationNode::Parameter> parameters, QString nodeName);

};

#endif // DIALOGNEWTREE_H
