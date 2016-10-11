#ifndef ROTATETRANSFORM_H
#define ROTATETRANSFORM_H
#include "augmentationnode.h"
#include <QDebug>
#include <QDoubleSpinBox>
#include <QtMath>

class AffineRotation : public AugmentationNode
{
public:
    AffineRotation();

    virtual void run();
    static QList<Parameter> parametersInterface();

private:
    cv::Size AffineRotation::largest_rotated_rect(int h, int w, double angle);
};

#endif // ROTATETRANSFORM_H
