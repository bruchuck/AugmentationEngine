#include "augmentationnode.h"
#include <QDoubleSpinBox>


AugmentationNode::AugmentationNode()
{

    name = "Root";
    index = 0;
    inputData = NULL;
    outputData = NULL;
    inputNode = NULL;
    height = 0;
    brothers = 0;

    QList<Parameter> params = parametersInterface();
    foreach(Parameter p, params){
        setParameter(p);
    }

}

AugmentationNode::~AugmentationNode()
{

}

void AugmentationNode::run()
{

    updateParameters();

    qDebug() << parametersList["enableScale"].value.toInt() << parametersList["xRes"].value.toInt() << parametersList["yRes"].value.toInt();
    if( parametersList["enableScale"].value.toInt() == 1){
        int xRes = parametersList["xRes"].value.toInt();
        int yRes = parametersList["yRes"].value.toInt();
        outputData = new Mat(xRes,yRes,inputData->type());
        resize(*inputData,*outputData,outputData->size(),0,0);
    }else{
        outputData = inputData;
    }
}

//exposed parameters to the interface
QList<AugmentationNode::Parameter> AugmentationNode::parametersInterface()
{

    QList<Parameter> parameters;

    Parameter enableScale;
    enableScale.name = "enableScale";
    enableScale.type = AugmentationNode::PARAMETER_FIXED;
    enableScale.min = 0;
    enableScale.max = 1;
    enableScale.value = 1;
    enableScale.widgetClassName = QDoubleSpinBox::staticMetaObject.className();

    Parameter xres;
    xres.name = "xRes";
    xres.type = AugmentationNode::PARAMETER_FIXED;
    xres.min = 1;
    xres.max = 5000;
    xres.value = 256;
    xres.widgetClassName = QDoubleSpinBox::staticMetaObject.className();

    Parameter yres;
    yres.name = "yRes";
    yres.type = AugmentationNode::PARAMETER_FIXED;
    yres.min = 1;
    yres.max = 5000;
    yres.value = 256;
    yres.widgetClassName = QDoubleSpinBox::staticMetaObject.className();

    parameters << enableScale << xres << yres;

    return parameters;
}


void AugmentationNode::saveOutputData(inputType data, QDir path)
{

    QString saveURL = QDir::cleanPath(path.absoluteFilePath(data.name))+ "_"+ name+QString::number(index) + ".jpg";
    saveURL.replace(" ", "_");

    if(!path.exists())
        path.mkpath(path.absolutePath());

    if(!imwrite(saveURL.toStdString().data(),*outputData))
        errorMessage = "Could not save the file";

    QFile file("result.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
           return;

    QTextStream out(&file);
    out << saveURL << " " << data.classification << "\n";
    file.close();
}

void AugmentationNode::clean()
{

    if(inputData){
        delete(inputData);
        inputData = NULL;
    }

    if(outputData){
        delete(outputData);
        outputData = NULL;
    }
    if(inputNode){
        delete(inputNode);
        inputNode = NULL;
    }

}

QString AugmentationNode::getName()
{
    return name;
}

int AugmentationNode::getIndex()
{
    return index;
}

void AugmentationNode::setIndex(int index)
{
    this->index = index;
}

void AugmentationNode::setInputNode(AugmentationNode* in)
{
    inputNode = in;

}

void AugmentationNode::setInputData(Mat* in)
{
    inputData = in;

}

void AugmentationNode::setParameter(QString name, QVariant value, PARAMETER_TYPE type, double min, double max, double sigma)
{

        Parameter p = parametersList[name];
        p.name = name;
        p.value = value;
        p.type = type;
        p.min = min;
        p.max = max;
        p.sigma = sigma;
        parametersList.insert(name,p);
}

void AugmentationNode::setParameter(QString name, double min, double max)
{
    setParameter(name,0.0,PARAMETER_UNIFORM,min,max,0.0);

}

void AugmentationNode::setParameter(Parameter p)
{
    setParameter(p.name,p.value,p.type,p.min,p.max,p.sigma);
}

QString* AugmentationNode::getErrorMessage()
{

    if(!errorMessage.isEmpty())
        return &errorMessage;
    else
        return NULL;
}

QMap<QString, AugmentationNode::Parameter> AugmentationNode::getParameters()
{
    return parametersList;
}

Mat *AugmentationNode::getOuput()
{
    return outputData;
}

//update the random parameters
void AugmentationNode::updateParameters()
{
    for(QMap<QString, AugmentationNode::Parameter>::iterator it = parametersList.begin(); it != parametersList.end(); ++it) {

        AugmentationNode::Parameter *p;
        p = &it.value();

        switch(p->type){
        case PARAMETER_UNIFORM:

            if(p->value.canConvert(QMetaType::Double)){

                p->value = cvrand.uniform(p->min,p->max);
            }
            else if(p->value.canConvert(QMetaType::QPointF)){

                p->value = QPointF(cvrand.uniform(p->min,p->max), cvrand.uniform(p->min,p->max));
            }

            break;
        case PARAMETER_GAUSSIAN:

            if(p->value.canConvert(QMetaType::Double)){

                p->value = cvrand.gaussian(p->sigma);
            }
            break;
        }
    }
}

//link the input with previous output and allocate outputData
void AugmentationNode::linkAndAllocate()
{
    inputData = inputNode->getOuput();
    if(inputData){

        if(outputData)
            delete(outputData);

        outputData = new Mat();
        *outputData = Mat::zeros(inputData->rows,inputData->cols,inputData->type());
    }
}

void AugmentationNode::deallocateOutput()
{
    if(outputData){
        delete(outputData);
        outputData = NULL;
    }
}



