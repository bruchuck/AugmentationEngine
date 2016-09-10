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

        Point2f p1, p2;

        int step = inputData->size().width/5;

        Point2f pts1[4];

        pts1[0] = Point2f(cvrand.uniform(step, 2 * step), cvrand.uniform(step, 2 * step));
        pts1[1] = Point2f(cvrand.uniform(3 * step, 4 * step), cvrand.uniform(step, 2 * step));
        pts1[2] = Point2f(cvrand.uniform(step, 2 * step), cvrand.uniform(3 * step, 4 * step));
        pts1[3] = Point2f(cvrand.uniform(3 * step, 4 * step), cvrand.uniform(3 * step, 4 * step));

        Point2f pts2[4];

        int offset = step/10;

        for (int i=0; i<4; i++)
            pts2[i] = Point2f(pts1[i].x + cvrand.uniform(-offset, +offset), pts1[i].y + cvrand.uniform(-offset, +offset));

        Mat transform = getPerspectiveTransform(pts1,pts2);
        warpPerspective(*inputData, *outputData,transform, inputData->size());
    }
}

QList<AugmentationNode::Parameter> WarpImage::parametersInterface()
{
    QList<AugmentationNode::Parameter> parameters;


    return parameters;
}

