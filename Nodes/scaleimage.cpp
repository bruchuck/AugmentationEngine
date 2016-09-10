#include "scaleimage.h"

ScaleImage::ScaleImage()
{
    name = "Scale";
}

void ScaleImage::run()
{

    //linkAndAllocate();
    //diferentSize allocation
    inputData = inputNode->getOuput();


    if(inputData){

        updateParameters();

        double scale = parametersList["Scale"].value.toDouble();
        outputData = new Mat();
        resize(*inputData,*outputData,Size(),scale,scale);

    }

}

QList<AugmentationNode::Parameter> ScaleImage::parametersInterface()
{

    QList<AugmentationNode::Parameter> parameters;


    Parameter scale;
    scale.name = "Scale";
    scale.type = AugmentationNode::PARAMETER_FIXED;
    scale.min = 0.01;
    scale.max = 1.00;
    scale.value = 0.5;
    scale.widgetClassName = QDoubleSpinBox::staticMetaObject.className();
    parameters << scale;

    return parameters;
}

