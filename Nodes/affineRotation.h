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
    Size largest_rotated_rect(int h, int w, double angle);
};

#endif // ROTATETRANSFORM_H
