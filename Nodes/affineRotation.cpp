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

        double angle = parametersList["angle"].value.toDouble();

        double scale = 1.0;
        if(parametersList.contains("scale"))
            scale = parametersList["scale"].value.toDouble();

        Mat transform = getRotationMatrix2D(center,angle,scale);
        warpAffine(*inputData,*outputData,transform,outputData->size());

        Size s= largest_rotated_rect(inputData->rows,inputData->cols,qDegreesToRadians(angle));

        Rect cropWindow(0.5*(inputData->rows - s.width),0.5*(inputData->cols - s.height), s.width, s.height);
        Mat image(*outputData);
        *outputData = image(cropWindow);

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

    parameters << angle ;

    return parameters;
}

Size AffineRotation::largest_rotated_rect(int h, int w, double angle)
{
    // Given a rectangle of size wxh that has been rotated by 'angle' (in
    // radians), computes the width and height of the largest possible
    // axis-aligned rectangle within the rotated rectangle.

    // Original JS code by 'Andri' and Magnus Hoff from Stack Overflow

    // Converted to Python by Aaron Snoswell (https://stackoverflow.com/questions/16702966/rotate-image-and-crop-out-black-borders)
    // Converted to C++ by Eliezer Bernart


    int quadrant = int(floor(angle/(M_PI/2))) & 3;
    double sign_alpha = ((quadrant & 1) == 0) ? angle : M_PI - angle;
    double alpha = fmod((fmod(sign_alpha, M_PI) + M_PI), M_PI);

    double bb_w = w * cos(alpha) + h * sin(alpha);
    double bb_h = w * sin(alpha) + h * cos(alpha);

    double gamma = w < h ? atan2(bb_w, bb_w) : atan2(bb_h, bb_h);

    double delta = M_PI - alpha - gamma;

    int length = w < h ? h : w;

    double d = length * cos(alpha);
    double a = d * sin(alpha) / sin(delta);
    double y = a * cos(gamma);
    double x = y * tan(gamma);

    return Size(bb_w - 2 * x, bb_h - 2 * y);
}


