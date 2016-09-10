#include "affineRotation.h"

AffineRotation::AffineRotation()
{
    name = "Rotation";
}

void AffineRotation::run()
{

    linkAndAllocate();

    if(inputData){

        updateParameters();

        Point2f center;
        center.x = (inputData->rows/2);
        center.y = (inputData->cols/2);

        if(parametersList.contains("center")){

            if(parametersList["center"].type == PARAMETER_UNIFORM || PARAMETER_GAUSSIAN){
                QPointF deltaCenter = parametersList["center"].value.toPointF();
                center.x += deltaCenter.x();
                center.y += deltaCenter.y();
            }
        }

        double angle = 1.0;
        if(parametersList.contains("angle")){
            angle = parametersList["angle"].value.toDouble();
        }

        double scale = 1.0;
        if(parametersList.contains("scale"))
            scale = parametersList["scale"].value.toDouble();


        Mat transform = getRotationMatrix2D(center,angle,scale);

        warpAffine(*inputData,*outputData,transform,outputData->size());

    }else
        errorMessage = "Input Data is invalid.";

}

//return a default value parameter to be exposed at the GUI.
QList<AugmentationNode::Parameter> AffineRotation::parametersInterface()
{
    QList<AugmentationNode::Parameter> parameters;

    AugmentationNode::Parameter angle;
    angle.name = "angle";
    angle.type = PARAMETER_UNIFORM;
    angle.min = -4.0;
    angle.max = +4.0;
    angle.value = 4.0;
    angle.widgetClassName = QDoubleSpinBox::staticMetaObject.className();

    AugmentationNode::Parameter center;
    center.name = "center";
    center.type = AugmentationNode::PARAMETER_FIXED;
    center.value = 1.0;
    center.widgetClassName = QDoubleSpinBox::staticMetaObject.className();

    parameters << angle << center;

    return parameters;
}



