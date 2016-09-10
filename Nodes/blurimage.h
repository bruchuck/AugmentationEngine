#ifndef BLURIMAGE_H
#define BLURIMAGE_H
#include "augmentationnode.h"
#include <QSpinBox>


class BlurImage : public AugmentationNode
{
public:
    BlurImage();
    virtual void run();
    static QList<Parameter> parametersInterface();
};

#endif // BLURIMAGE_H
