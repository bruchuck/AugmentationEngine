#ifndef NOISEIMAGE_H
#define NOISEIMAGE_H
#include "augmentationnode.h"
#include <QDoubleSpinBox>

class NoiseImage : public AugmentationNode
{
public:
    NoiseImage();
    virtual void run();
    static QList<Parameter> parametersInterface();
};

#endif // NOISEIMAGE_H
