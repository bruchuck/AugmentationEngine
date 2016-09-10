#ifndef ENUMS
#define ENUMS
#include <QString>
#include <QList>
#include <QDir>
#include <QVariant>
#include <opencv2/core/core.hpp>

#define GRAPHICWIDTH 70.0

struct inputType{
  QString name, classification;
  QDir path;
};

struct LayerData{
    int priority;
    int hMin, hMax, brothersMin, brothersMax;
};

static cv::RNG cvrand;
#endif // ENUMS

