#include "noiseimage.h"

NoiseImage::NoiseImage()
{
    name = "Noise";
}

void NoiseImage::run()
{

    linkAndAllocate();
    if(inputData){


        updateParameters();

        Mat noise = Mat(Size(inputData->cols,inputData->rows),inputData->type());

        int std = parametersList["stdDeviation"].value.toInt();
        randn(noise,0,std);

        *outputData = *inputData + noise;

    }
}

QList<AugmentationNode::Parameter> NoiseImage::parametersInterface()
{
    QList<AugmentationNode::Parameter> parameters;


    Parameter stdDeviation;
    stdDeviation.name = "stdDeviation";
    stdDeviation.type = AugmentationNode::PARAMETER_UNIFORM;
    stdDeviation.min = 5;
    stdDeviation.max = 15;
    stdDeviation.value = 0;
    stdDeviation.widgetClassName = QDoubleSpinBox::staticMetaObject.className();
    parameters << stdDeviation;

    return parameters;

}

