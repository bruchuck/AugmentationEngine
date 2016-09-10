#include "contrastimage.h"

ContrastImage::ContrastImage()
{

    name = "Contrast";
}

void ContrastImage::run()
{

    linkAndAllocate();
    if(inputData){

        updateParameters();

        if(parametersList.contains("contrast")){

            qDebug() << parametersList["contrast"].value.toDouble();
           inputData->convertTo(*outputData,-1,parametersList["contrast"].value.toDouble(),0.0);
        }
    }

}

QList<AugmentationNode::Parameter> ContrastImage::parametersInterface()
{
     QList<AugmentationNode::Parameter> parameters;

     Parameter contrast;
     contrast.name = "contrast";
     contrast.type = AugmentationNode::PARAMETER_UNIFORM;
     contrast.min = 0.5;
     contrast.max = 2.0;
     contrast.value = 0.0;
     contrast.widgetClassName = QDoubleSpinBox::staticMetaObject.className();
     parameters << contrast;

     return parameters;
}
