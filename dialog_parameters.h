#ifndef DIALOG_PARAMETERS_H
#define DIALOG_PARAMETERS_H

#include <QDialog>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QDebug>
#include <QComboBox>
#include <QMap>
#include "defenums.h"
#include "augmentationnode.h"

namespace Ui {
class Dialog_Parameters;
}

class Dialog_Parameters : public QDialog
{
    Q_OBJECT

public:

    struct DialogData{
        QString nodeName;
        QList<AugmentationNode::Parameter> parameters;
        int layerIndex;
    };

    explicit Dialog_Parameters(QWidget *parent = 0);
    void addParameter(AugmentationNode::Parameter p);
    void fillRandomComboBox(QComboBox *combo);

    QList<AugmentationNode::Parameter> getParameters();

    ~Dialog_Parameters();

public slots:
    void comboBox_currentIndexChanged(const QString &comboType);
    void doubleSpinBox_changed(double value);

private:
    Ui::Dialog_Parameters *ui;
    QMap<QWidget*,AugmentationNode::Parameter> parameterMap;
};

#endif // DIALOG_PARAMETERS_H
