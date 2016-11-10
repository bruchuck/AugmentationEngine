#ifndef TRANSLATION_H
#define TRANSLATION_H
#include "augmentationnode.h"
#include <QDoubleSpinBox>

class Translation : public AugmentationNode
{
public:
    Translation();

    virtual void run();
    static QList<Parameter> parametersInterface();
};

#endif // TRANSLATION_H
