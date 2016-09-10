#include "dialog_newtree.h"
#include "ui_dialog_newtree.h"

DialogNewTree::DialogNewTree(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewTree)
{
    ui->setupUi(this);

    //populate comboBoxes
    QList<QComboBox *> comboList = this->findChildren<QComboBox*>();
    foreach(QComboBox * combo, comboList){
        combo->addItem("Layer 0",0);
    }

    createDialogDataInterface();

    //create default LayerData
    LayerData layerData;
    layerData.priority = 0;
    layerData.hMin = qobject_cast<QSpinBox *>(ui->layerLayout->itemAtPosition(0+1,1)->widget())->value();
    layerData.hMax = qobject_cast<QSpinBox *>(ui->layerLayout->itemAtPosition(0+1,2)->widget())->value();
    layerData.brothersMin = qobject_cast<QSpinBox *>(ui->layerLayout->itemAtPosition(0+1,3)->widget())->value();
    layerData.brothersMax = qobject_cast<QSpinBox *>(ui->layerLayout->itemAtPosition(0+1,4)->widget())->value();
    layers << layerData;

    //connect spinBox objects signals and slots
     QList<QSpinBox *> spinList = this->findChildren<QSpinBox*>();
     if(!spinList.isEmpty()){
         foreach(QSpinBox *spin, spinList){
             connect(spin,SIGNAL(valueChanged(int)),this,SLOT(spinBoxChanged(int)));
             spin->valueChanged(spin->value());
         }
     }

}

DialogNewTree::~DialogNewTree()
{
    delete ui;
}

//return a list of checked node types in a priority ordered map
QMap<int, Dialog_Parameters::DialogData> DialogNewTree::getDialogData()
{
    QMap<int, Dialog_Parameters::DialogData> checkedNodes;

    QList<QCheckBox *> list = this->findChildren<QCheckBox*>();
    if(!list.isEmpty()){

        foreach(QCheckBox *box, list){

            if(box->isChecked()){

                Dialog_Parameters::DialogData data = dialogDataMap[box->text()];

                qDebug() << data.nodeName << "param " << data.parameters.size();
                checkedNodes.insertMulti(data.layerIndex,data);
            }
        }
    }

    return checkedNodes;
}

//create the DialogData and interface for each node type
void DialogNewTree::createDialogDataInterface()
{
    //create Dialog Data Interface;
    QList<QCheckBox *> list = this->findChildren<QCheckBox*>();
    if(!list.isEmpty()){

        foreach(QCheckBox *box, list){

            QGridLayout* gridLayout = box->parentWidget()->findChild<QGridLayout*>();
            int row, col, row_s, col_s;
            gridLayout->getItemPosition(gridLayout->indexOf(box),&row,&col,&row_s,&col_s);

            //get priority box
            QComboBox *priority = qobject_cast<QComboBox *>(gridLayout->itemAtPosition(row,1)->widget());

            //get configure parameters button
            QPushButton *configParam = qobject_cast<QPushButton *>(gridLayout->itemAtPosition(row,2)->widget());
            connect(configParam,SIGNAL(pressed()),this,SLOT(changeParameters_clicked()));

            Dialog_Parameters::DialogData nodeData;
            nodeData.nodeName = box->text();
            nodeData.layerIndex = priority->currentData().toInt();

            //populate dialogData with default values
            QList<AugmentationNode::Parameter> parameters = AugmentationTree::getParametersInterface(nodeData.nodeName);
            nodeData.parameters = parameters;

            dialogDataMap.insert(nodeData.nodeName,nodeData);
        }
    }
}

//create the GUI parameter interface for a specific nodeName
void DialogNewTree::createParameterDialog(QList<AugmentationNode::Parameter> parameters, QString nodeName)
{
    Dialog_Parameters* dialog;

    dialog = this->findChild<Dialog_Parameters*>(nodeName);

    if(dialog == NULL){
        dialog = new Dialog_Parameters(this);

        connect(dialog,SIGNAL(accepted()),this,SLOT(setNodeParameters()));

        foreach(AugmentationNode::Parameter p, parameters){
            dialog->addParameter(p);
        }
        dialog->setWindowTitle(nodeName);
        dialog->setObjectName(nodeName);
        dialog->show();
    }else{
        dialog->show();
    }
}

//Slot change parameters button clicked
void DialogNewTree::changeParameters_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QGridLayout* gridLayout = button->parentWidget()->findChild<QGridLayout*>();
    int row, col, row_s, col_s;
    gridLayout->getItemPosition(gridLayout->indexOf(button),&row,&col,&row_s,&col_s);
    QString nodeName = qobject_cast<QCheckBox *>(gridLayout->itemAtPosition(row,0)->widget())->text();


    QList<AugmentationNode::Parameter> parameters = AugmentationTree::getParametersInterface(nodeName);

    createParameterDialog(parameters,nodeName + " Parameters");
}

//set node parameters in the dialog data map
void DialogNewTree::setNodeParameters()
{
    Dialog_Parameters* nodeParameters = qobject_cast<Dialog_Parameters*>(sender());

    QString nodeName = nodeParameters->windowTitle();
    nodeName.chop(11);

    qDebug() << nodeName;
    if(dialogDataMap.contains(nodeName)){
        dialogDataMap[nodeName].parameters = nodeParameters->getParameters();
    }else
        qDebug() << "error, dialogData do not contains node with name: " << nodeName;
}

//Slot: changed value in a layer spinbox
void DialogNewTree::spinBoxChanged(int value)
{

    QSpinBox * spin = qobject_cast<QSpinBox*>(sender());
    QGridLayout* gridLayout = spin->parentWidget()->findChild<QGridLayout*>();
    int row, col, row_s, col_s;
    gridLayout->getItemPosition(gridLayout->indexOf(spin),&row,&col,&row_s,&col_s);

    if(gridLayout->objectName() == "layerLayout"){

        QSpinBox * min;

        switch(col){

        case 1:
            layers[row-1].hMin = value;
            break;
        case 2:
            layers[row-1].hMax = value;
            min = qobject_cast<QSpinBox*>(gridLayout->itemAtPosition(row,1)->widget());
            min->setMaximum(value);
            break;
        case 3:
            layers[row-1].brothersMin = value;
            break;
        case 4:
            layers[row-1].brothersMax = value;
            min = qobject_cast<QSpinBox*>(gridLayout->itemAtPosition(row,3)->widget());
            min->setMaximum(value);
            break;
        default:
            qDebug() << "SpinBox Code not implemented";
        }

    }

}
