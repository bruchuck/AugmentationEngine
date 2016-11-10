#include "castcolor.h"

CastColor::CastColor()
{
    name="CastColor";
}

void CastColor::run()
{

    linkAndAllocate();

    if(inputData){

        updateParameters();

        float r = parametersList["R"].value.toFloat();
        float g = parametersList["G"].value.toFloat();
        float b = parametersList["B"].value.toFloat();

        qDebug() << r, g, b;
        Scalar color(r,g,b);
        add(*inputData,color,*outputData);
    }

}

QList<AugmentationNode::Parameter> CastColor::parametersInterface()
{

    QList<AugmentationNode::Parameter> parameters;

    Parameter RColor;
    RColor.name = "R";
    RColor.type = AugmentationNode::PARAMETER_UNIFORM;
    RColor.min = -25.00;
    RColor.max = 25.0;
    RColor.value = 0.00;
    RColor.widgetClassName = QDoubleSpinBox::staticMetaObject.className();
    parameters << RColor;

    Parameter GColor;
    GColor.name = "G";
    GColor.type = AugmentationNode::PARAMETER_UNIFORM;
    GColor.min = -25.00;
    GColor.max = 25.00;
    GColor.value = 0.00;
    GColor.widgetClassName = QDoubleSpinBox::staticMetaObject.className();
    parameters << GColor;

    Parameter BColor;
    BColor.name = "B";
    BColor.type = AugmentationNode::PARAMETER_UNIFORM;
    BColor.min = -25.00;
    BColor.max = 25.00;
    BColor.value = 0.00;
    BColor.widgetClassName = QDoubleSpinBox::staticMetaObject.className();
    parameters << BColor;


    return parameters;

}

