#include "translation.h"

Translation::Translation()
{

    name = "Translation";
}

void Translation::run()
{

    linkAndAllocate();
    if(inputData){

        updateParameters();

        int tx =0, ty =0;

        if(parametersList.contains("tx"))
            tx = parametersList["tx"].value.toInt();
        if(parametersList.contains("ty"))
            tx = parametersList["ty"].value.toInt();

        Mat transform = (Mat_<double>(2,3) << 1, 0, tx, 0, 1, ty);

        warpAffine(*inputData,*outputData,transform,inputData->size());

    }
}

QList<AugmentationNode::Parameter> Translation::parametersInterface()
{
    QList<AugmentationNode::Parameter> parameters;

    Parameter coordX;
    coordX.name = "tx";
    coordX.type = AugmentationNode::PARAMETER_UNIFORM;
    coordX.min = -20;
    coordX.max = +20;
    coordX.value = 1.0;
    coordX.widgetClassName = QDoubleSpinBox::staticMetaObject.className();

    Parameter coordY;
    coordY.name = "ty";
    coordY.type = AugmentationNode::PARAMETER_UNIFORM;
    coordY.min = -20;
    coordY.max = +20;
    coordY.value = 1.0;
    coordY.widgetClassName = QDoubleSpinBox::staticMetaObject.className();

    parameters << coordX << coordY;

    return parameters;
}

