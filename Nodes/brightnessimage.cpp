#include "brightnessimage.h"

BrightnessImage::BrightnessImage()
{

    name = "Brightness";
}

void BrightnessImage::run()
{
    linkAndAllocate();



    if(inputData){


        updateParameters();

        if(parametersList.contains("brightness")){

            qDebug() << "value of" << parametersList["brightness"].value.toDouble();
            inputData->convertTo(*outputData,-1,1.0,parametersList["brightness"].value.toDouble());
        }
    }
}

QList<AugmentationNode::Parameter> BrightnessImage::parametersInterface()
{
     QList<AugmentationNode::Parameter> parameters;

     Parameter brightness;
     brightness.name = "brightness";
     brightness.type = AugmentationNode::PARAMETER_UNIFORM;
     brightness.min = -25;
     brightness.max = 25;
     brightness.value = 0;
     brightness.widgetClassName = QDoubleSpinBox::staticMetaObject.className();
     parameters << brightness;

     return parameters;
}

