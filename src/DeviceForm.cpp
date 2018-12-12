#include "DeviceForm.h"

/******************************************************************************
* Storage Device Form                                                         *
******************************************************************************/

DeviceStorageForm::DeviceStorageForm(DeviceStorage *dev) : device(dev)
{
    QGroupBox *ideFormGroup = this;
    QLineEdit *imageLine = new QLineEdit(ideFormGroup);
    QPushButton *selectImageBtn = new QPushButton("...", ideFormGroup);

    selectImageBtn->setFixedWidth(30);
    imageLine->setText(device->getImage());
    imageLine->setReadOnly(true);
    if (device->getImage().isEmpty())
    {
        imageLine->setStyleSheet("background: #EE756F");
    }

    QVBoxLayout *mainLay = new QVBoxLayout();
    QHBoxLayout *topLay = new QHBoxLayout();
    topLay->addWidget(imageLine);
    topLay->addWidget(selectImageBtn);

    mainLay->addLayout(topLay);
    mainLay->addStretch(500);

    ideFormGroup->setLayout(mainLay);
    connect(selectImageBtn, &QPushButton::clicked, this, &DeviceStorageForm::editImage);
    connect(this, SIGNAL(newImageSet(QString)), imageLine, SLOT(setText(QString)));
    connect(this, SIGNAL(newDiskCompleted(QString)), imageLine, SLOT(setStyleSheet(QString)));
}

void DeviceStorageForm::editImage()
{
    QString newImage = QFileDialog::getOpenFileName(nullptr, "Selecting image",
        "", "*.qcow *.qcow2 *.img *.raw");
    if (!newImage.isEmpty())
    {
        emit newImageSet(newImage);
        emit newDiskCompleted("");
        device->setImage(newImage);
    }
}

/******************************************************************************
* SCSI Controller Form                                                        *
******************************************************************************/

DeviceScsiControllerForm::DeviceScsiControllerForm(DeviceScsiController *dev) :
    device(dev)
{
    QGroupBox *scsiFormGroup = this;
    QComboBox *controllersCombo = new QComboBox();

    controllersCombo->addItems(device->getControllers());
    controllersCombo->setCurrentText(device->getCurrentController());

    QVBoxLayout *mainLay = new QVBoxLayout();
    mainLay->addWidget(controllersCombo);
    mainLay->addStretch(500);

    scsiFormGroup->setLayout(mainLay);

    connect(controllersCombo, SIGNAL(currentIndexChanged(const QString &)),
        this, SLOT(setController(const QString &)));
}

void DeviceScsiControllerForm::setController(const QString &name)
{
    device->setController(name);
}