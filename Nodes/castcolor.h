#ifndef CASTCOLOR_H
#define CASTCOLOR_H
#include "augmentationnode.h"

class CastColor : public AugmentationNode
{
public:
    CastColor();
    virtual void run();
    static QList<Parameter> parametersInterface();

};

#endif // CASTCOLOR_H
