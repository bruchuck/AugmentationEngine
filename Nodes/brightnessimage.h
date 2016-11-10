#ifndef BRIGHTNESSIMAGE_H
#define BRIGHTNESSIMAGE_H
#include "augmentationnode.h"
#include <QDoubleSpinBox>

class BrightnessImage : public AugmentationNode
{
public:
    BrightnessImage();
    virtual void run();
    static QList<Parameter> parametersInterface();
};

#endif // BRIGHTNESSIMAGE_H
