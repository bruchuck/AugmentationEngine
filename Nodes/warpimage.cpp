#include "warpimage.h"

WarpImage::WarpImage()
{
    name= "Warp";

}

void WarpImage::run()
{

    linkAndAllocate();
    if(inputData){

        updateParameters();

        float dx = parametersList.value("step").value.toFloat();
        int step = inputData->size().width * dx;

        Point2f pts1[4], pts2[4];
        pts2[0] = Point2f(0, 0);
        pts2[1] = Point2f(inputData->size().width, 0);
        pts2[2] = Point2f(0, inputData->size().height);
        pts2[3] = Point2f(inputData->size().width, inputData->size().height);

        pts1[0] = pts2[0] + Point2f(cvrand.uniform(0, step), cvrand.uniform(0, step));
        pts1[1] = pts2[1] + Point2f(cvrand.uniform(-step, 0), cvrand.uniform(0, step));
        pts1[2] = pts2[2] + Point2f(cvrand.uniform(0, step), cvrand.uniform(-step, 0));
        pts1[3] = pts2[3] + Point2f(cvrand.uniform(-step, 0), cvrand.uniform(-step, 0));

        Mat transform = getPerspectiveTransform(pts1,pts2);
        warpPerspective(*inputData, *outputData,transform, inputData->size());
    }
}

QList<AugmentationNode::Parameter> WarpImage::parametersInterface()
{
    QList<AugmentationNode::Parameter> parameters;

    Parameter step;
    step.name = "step";
    step.type = AugmentationNode::PARAMETER_FIXED;
    step.min = -0.05;
    step.max = +0.05;
    step.value = 0.05;
    step.widgetClassName = QDoubleSpinBox::staticMetaObject.className();

    parameters << step;
    return parameters;
}

