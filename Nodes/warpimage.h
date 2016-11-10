#ifndef WARPIMAGE_H
#define WARPIMAGE_H
#include <augmentationnode.h>
#include <QDoubleSpinBox>

class WarpImage : public AugmentationNode
{
public:
    WarpImage();
    virtual void run();
    static QList<Parameter> parametersInterface();
};

#endif // WARPIMAGE_H
