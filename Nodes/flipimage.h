#ifndef FLIPIMAGE_H
#define FLIPIMAGE_H
#include "augmentationnode.h"


class FlipImage : public AugmentationNode
{
public:
    FlipImage();

    virtual void run();
    static QList<AugmentationNode::Parameter> parametersInterface();
};

#endif // FLIPIMAGE_H
