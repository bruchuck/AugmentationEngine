#include "dialog_parameters.h"
#include "ui_dialog_parameters.h"

Dialog_Parameters::Dialog_Parameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Parameters)
{
    ui->setupUi(this);
}

void Dialog_Parameters::addParameter(AugmentationNode::Parameter p)
{

    QLabel *name =new QLabel(p.name);
    ui->mainLayout->addWidget(name,ui->mainLayout->rowCount(),0);

    if(p.widgetClassName == QDoubleSpinBox::staticMetaObject.className()){

        QComboBox *box = new QComboBox;

        ui->mainLayout->addWidget(box,ui->mainLayout->rowCount()-1,1);
        fillRandomComboBox(box);

        QDoubleSpinBox* spinBox = ui->mainLayout->itemAtPosition(ui->mainLayout->rowCount()-1,2)->widget()->findChild<QDoubleSpinBox*>();

        if(p.type == AugmentationNode::PARAMETER_UNIFORM){
            spinBox->setValue(p.min);
            QDoubleSpinBox* spinBox2 =ui->mainLayout->itemAtPosition(ui->mainLayout->rowCount()-1,3)->widget()->findChild<QDoubleSpinBox*>();
            spinBox2->setValue(p.max);

        }else if(p.type == AugmentationNode::PARAMETER_GAUSSIAN){
            box->setCurrentIndex(1);
            spinBox->setValue(p.sigma);
        }else if(p.type == AugmentationNode::PARAMETER_FIXED){
            box->setCurrentIndex(2);
            spinBox->setValue(p.value.toDouble());
        }
    }


    parameterMap.insert(name,p);
}

void Dialog_Parameters::fillRandomComboBox(QComboBox *combo)
{
    combo->addItem("Uniform");
    combo->addItem("Gaussian");
    combo->addItem("Fixed");

    int row, col, row_s, col_s;
    ui->mainLayout->getItemPosition(ui->mainLayout->indexOf(combo),&row,&col,&row_s,&col_s);

    //uniform input

    QDoubleSpinBox *min = new QDoubleSpinBox();
    min->setMinimum(-999999);
    QDoubleSpinBox *max = new QDoubleSpinBox();
    min->setMaximum(999999);
    QLabel *minLabel = new QLabel("Min: ");
    QLabel *maxLabel = new QLabel("Max: ");

    QWidget *minWidget = new QWidget();
    QHBoxLayout *minlayout = new QHBoxLayout();
    minlayout->addWidget(minLabel);
    minlayout->addWidget(min);
    minWidget->setLayout(minlayout);
    minlayout->setContentsMargins(0,0,0,0);


    QWidget *maxWidget = new QWidget();
    QHBoxLayout *maxlayout = new QHBoxLayout();
    maxlayout->addWidget(maxLabel);
    maxlayout->addWidget(max);
    maxWidget->setLayout(maxlayout);
    maxlayout->setContentsMargins(0,0,0,0);

    ui->mainLayout->addWidget(minWidget,row,col+1);
    ui->mainLayout->addWidget(maxWidget,row,col+2);

    connect(combo,SIGNAL(currentIndexChanged(QString)),this,SLOT(comboBox_currentIndexChanged(QString)));
    connect(min,SIGNAL(valueChanged(double)),this,SLOT(doubleSpinBox_changed(double)));
}

QList<AugmentationNode::Parameter> Dialog_Parameters::getParameters()
{
    return parameterMap.values();
}


Dialog_Parameters::~Dialog_Parameters()
{
    delete ui;
}

//slot for changed random type combobox
void Dialog_Parameters::comboBox_currentIndexChanged(const QString &comboType)
{
    QComboBox *box = qobject_cast<QComboBox*>(sender());
    if( box != NULL ) {

        QGridLayout* gridLayout = box->parentWidget()->findChild<QGridLayout*>();
        int row, col, row_s, col_s;
        gridLayout->getItemPosition(gridLayout->indexOf(box),&row,&col,&row_s,&col_s);

        if(comboType == "Uniform"){

             gridLayout->itemAtPosition(row,col+2)->widget()->show();
             gridLayout->itemAtPosition(row,col+1)->widget()->findChild<QLabel *>()->setText("Min :");


        }else if(comboType == "Gaussian"){

             gridLayout->itemAtPosition(row,col+2)->widget()->hide();
             gridLayout->itemAtPosition(row,col+1)->widget()->findChild<QLabel *>()->setText("Sigma :");


        }else if(comboType == "Fixed"){

             gridLayout->itemAtPosition(row,col+2)->widget()->hide();
             gridLayout->itemAtPosition(row,col+1)->widget()->findChild<QLabel *>()->setText("Value :");
        }
    }
}

//Slot for changes in a paramter spinbox
void Dialog_Parameters::doubleSpinBox_changed(double value)
{
    QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(sender());

    int row, col, row_s, col_s;
    //ui->mainLayout>getItemPosition(ui->mainLayout->indexOf(spinBox),&row,&col,&row_s,&col_s);


}
