#include "flipimage.h"

FlipImage::FlipImage()
{

    name = "Flip";
}

void FlipImage::run()
{

    linkAndAllocate();

    if(inputData){

        updateParameters();
        if(parametersList.contains("orientation")){
            //angle = parametersList["orientation"].value.toDouble();
        }

        flip(*inputData,*outputData,1);
    }
}

QList<AugmentationNode::Parameter> FlipImage::parametersInterface()
{

    QList<AugmentationNode::Parameter> parameters;

    return parameters;
}

