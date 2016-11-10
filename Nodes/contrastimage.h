#ifndef CONTRASTIMAGE_H
#define CONTRASTIMAGE_H
#include "augmentationnode.h"

class ContrastImage : public AugmentationNode
{
public:
    ContrastImage();
    virtual void run();
    static QList<Parameter> parametersInterface();
};

#endif // CONTRASTIMAGE_H
