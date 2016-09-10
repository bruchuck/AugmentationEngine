#ifndef AUGMENTATIONNODE_H
#define AUGMENTATIONNODE_H
#include <QList>
#include <ogdf/basic/Graph.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/tree/TreeLayout.h>
#include <QDebug>
#include <QString>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <defenums.h>
#include <QVariant>


using namespace cv;
class AugmentationNode
{
public:

    enum PARAMETER_TYPE{
        PARAMETER_FIXED = 0,
        PARAMETER_UNIFORM = 1,
        PARAMETER_GAUSSIAN = 2
    };

    struct Parameter{
        QVariant value;
        QString name;
        QString widgetClassName;
        PARAMETER_TYPE type;
        double min, max;
        double sigma;
    };

    AugmentationNode();
    ~AugmentationNode();

    static QList<AugmentationNode::Parameter> parametersInterface();

    virtual void run();


    virtual void saveOutputData(inputType data, QDir path);
    virtual void deallocateOutput();
    virtual void clean();


    int getIndex();
    void setIndex(int index);
    void setInputNode(AugmentationNode* in);
    void setInputData(Mat* in);

    void setParameter(QString name, QVariant value, PARAMETER_TYPE type= PARAMETER_FIXED, double min= 0.0, double max = 0.0, double sigma = 0.0);
    void setParameter(QString name, double min, double max);
    void setParameter(Parameter p);

    QString getName();
    QString* getErrorMessage();
    QMap<QString, Parameter> getParameters();

    Mat* getOuput();

    int height, brothers;
protected:

    Mat *inputData, *outputData;

    QMap<QString, Parameter> parametersList;

    AugmentationNode* inputNode;


    QString name;
    int index;

    QString errorMessage;

    void updateParameters();

    void linkAndAllocate();


private:



};
#endif // AUGMENTATIONNODE_H
