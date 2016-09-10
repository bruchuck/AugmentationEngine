#ifndef SCALEIMAGE_H
#define SCALEIMAGE_H
#include <augmentationnode.h>
#include <QDoubleSpinBox>

class ScaleImage : public AugmentationNode
{
public:
    ScaleImage();
    virtual void run();
    static QList<Parameter> parametersInterface();
};

#endif // SCALEIMAGE_H
