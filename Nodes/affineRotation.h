#ifndef ROTATETRANSFORM_H
#define ROTATETRANSFORM_H
#include "augmentationnode.h"
#include <QDebug>
#include <QDoubleSpinBox>

class AffineRotation : public AugmentationNode
{
public:
    AffineRotation();

    virtual void run();
    static QList<Parameter> parametersInterface();
};

#endif // ROTATETRANSFORM_H
