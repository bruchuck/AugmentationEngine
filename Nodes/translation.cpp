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


        int x1,x2, y1, y2;
        if(tx> 0){
            x1 = 0 + tx;
            x2 = outputData->rows-1;
        }else{
            x1 = 0;
            x2 = outputData->rows -1 +tx;
        }

        if(ty > 0){
            y1 = 0 + ty;
            y2 = outputData->cols-1;
        }else{
            y1 = 0;
            y2 = outputData->cols-1 +ty;
        }


        Rect cropWindow(Point(x1,y1),Point(x2,y2));
        Mat image(*outputData);
        *outputData = image(cropWindow);

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

