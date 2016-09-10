#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <augmentationnode.h>
#include <defenums.h>
#include <QDateTime>
#include <QMouseEvent>
#include <QDir>

class LogManager{

public:

    struct error{
        QString Sender;
        QString Message;
    };

    LogManager(QString log);

    //write node log message
    void startLog();
    void LogNode(AugmentationNode* node);
    void LogLoadImage(inputType image, bool result, QString message = QString());
    void closeLog();

    void printErrors();

    //recover tree state from Log File
    bool RecoverFromLog();

protected:



private:



     QFile* logFile;
     QXmlStreamWriter* xmlWriter;

     bool openedFile = false;

     QList<error> errorList;

};

#endif // FILEMANAGER_H
