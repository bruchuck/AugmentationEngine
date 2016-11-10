#include "logmanager.h"

LogManager::LogManager(QString log){

    logFile = new QFile(log);
    xmlWriter = NULL;

}

void LogManager::startLog()
{

    if(!logFile->open(QIODevice::WriteOnly)){
        qWarning ("could not open log file");
        return;
    }


    xmlWriter = new QXmlStreamWriter(logFile);
    xmlWriter->setAutoFormatting(true);
    xmlWriter->writeStartDocument();
    xmlWriter->writeStartElement("Log");
}


void LogManager::LogNode(AugmentationNode* node)
{
    if(!xmlWriter){
        qWarning ("log and fail recovery is disabled.");
        return;
    }

    xmlWriter->writeStartElement("Node");
    xmlWriter->writeAttribute("index",QString::number(node->getIndex()));
    xmlWriter->writeTextElement("Name",node->getName());

    //log parameters of the node.
    QMap<QString, AugmentationNode::Parameter> nodeParameters = node->getParameters();
    if(!nodeParameters.isEmpty()){
        xmlWriter->writeStartElement("Parameters");
        foreach(AugmentationNode::Parameter p, nodeParameters){
            if(p.value.canConvert<QString>())
                xmlWriter->writeTextElement(p.name,p.value.toString());
            else if(p.value.canConvert<QPointF>()){
                xmlWriter->writeStartElement("PointF");
                xmlWriter->writeAttribute("x",QString::number(p.value.toPointF().x()));
                xmlWriter->writeAttribute("y",QString::number(p.value.toPointF().y()));
                xmlWriter->writeEndElement();
            }else{
                qDebug() << "cant log parameter of type :" << p.value.typeName();
            }
        }
        xmlWriter->writeEndElement();
    }
    xmlWriter->writeStartElement("Result");
    xmlWriter->writeAttribute("Operation","Execute_Node");

    if(!node->getErrorMessage())
        xmlWriter->writeAttribute("success","true");
    else{

        error err;
        err.Message = *node->getErrorMessage();
        err.Sender = "Node "+ node->getName();
        errorList << err;

        xmlWriter->writeAttribute("sucess","false");
        xmlWriter->writeTextElement("Message", err.Message);

    }

    xmlWriter->writeTextElement("Time", QDateTime::currentDateTime().toString(Qt::TextDate));
    //xmlWriter->writeTextElement("URL",node->);
    xmlWriter->writeEndElement();
    xmlWriter->writeEndElement();

}

void LogManager::LogLoadImage(inputType image, bool result, QString message )
{

    if(openedFile)
        xmlWriter->writeEndElement();

    xmlWriter->writeStartElement("Image");

    xmlWriter->writeAttribute("name", image.name);

    xmlWriter->writeStartElement("Result");
    xmlWriter->writeAttribute("Operation","Load_Image");
    if(result)
        xmlWriter->writeAttribute("success","true");
    else{
        xmlWriter->writeAttribute("success","false");
        xmlWriter->writeTextElement("Message", message);
        error err;
        err.Message = message;
        err.Sender = "Image " + image.name;
        errorList << err;
    }

    xmlWriter->writeTextElement("URL",image.path.absolutePath());
    xmlWriter->writeTextElement("Time", QDateTime::currentDateTime().toString(Qt::TextDate));

    xmlWriter->writeEndElement();
    openedFile = true;
}

//close the log file
void LogManager::closeLog()
{
    if(!xmlWriter){
        qWarning ("log and fail recovery is disabled.");
        return;
    }

    xmlWriter->writeEndDocument();
    logFile->close();
}

void LogManager::printErrors()
{

    qDebug() << "There were " + QString::number(errorList.size()) + " errors:";
    foreach(error err, errorList){
        qDebug() << err.Sender  << " : "<< err.Message;
    }
}

//recover from log file
bool LogManager::RecoverFromLog()
{
    return true;
}





