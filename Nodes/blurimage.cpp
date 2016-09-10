#include "blurimage.h"

BlurImage::BlurImage()
{

    name = "Blur";
}

void BlurImage::run()
{

    linkAndAllocate();

    if(inputData){

        updateParameters();


        int kSize = parametersList["KernelSize"].value.toInt();
        qDebug() << "size =" << kSize ;
        if(kSize%2 == 0){
            kSize= kSize+1;
        }

        double sigma = parametersList["Sigma"].value.toDouble();

        GaussianBlur(*inputData,*outputData,Size(kSize,kSize),-1,-1);

    }
}

QList<AugmentationNode::Parameter> BlurImage::parametersInterface()
{

    QList<AugmentationNode::Parameter> parameters;

    Parameter kernelSize;
    kernelSize.name = "KernelSize";
    kernelSize.type = AugmentationNode::PARAMETER_UNIFORM;
    kernelSize.min = 9;
    kernelSize.max = 31;
    kernelSize.value = 5;
    kernelSize.widgetClassName = QSpinBox::staticMetaObject.className();
    parameters << kernelSize;

    Parameter sigma;
    sigma.name = "Sigma";
    sigma.type = AugmentationNode::PARAMETER_UNIFORM;
    sigma.min = 0.8;
    sigma.max = 0.95;
    sigma.value = 0.95;
    sigma.widgetClassName = QSpinBox::staticMetaObject.className();
    parameters << sigma;

    return parameters;
}

