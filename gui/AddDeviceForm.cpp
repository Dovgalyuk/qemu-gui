#include "AddDeviceForm.h"
#include "DeviceFactory.h"
#include "device/DeviceConfiguration.h"
#include "QemuGUI.h"


AddDeviceForm::AddDeviceForm(const Device *device, QWidget *parent)
{
    if (AddDeviceForm::objectName().isEmpty())
        AddDeviceForm::setObjectName(QStringLiteral("AddDeviceForm"));
    resize(140, 200);
    setWindowTitle(QApplication::translate("AddDeviceForm", "Add device", Q_NULLPTR));
    setWindowModality(Qt::WindowModality::ApplicationModal);

    deviceList = new QListWidget();
    QPushButton *addBtn = new QPushButton("Add");
    QPushButton *cancelBtn = new QPushButton("Cancel");

    addBtn->setDefault(true);
    cancelBtn->setAutoDefault(true);

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    QHBoxLayout *btnLay = new QHBoxLayout();
    btnLay->addWidget(addBtn);
    btnLay->addWidget(cancelBtn);

    mainLay->addWidget(deviceList);
    mainLay->addLayout(btnLay);

    setLayout(mainLay);

    connect(addBtn, &QPushButton::clicked, this, &AddDeviceForm::addNewDevice);
    connect(cancelBtn, &QPushButton::clicked, this, &QWidget::close);
    connect(deviceList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), 
        this, SLOT(addNewDeviceDblClick(QListWidgetItem *)));

    // DeviceFactory for everything
    if (device->providesBus() != BusType::None)
    {
        addDevices = DeviceFactory::getDevicesForBus(device->providesBus());
        foreach(auto dev, addDevices)
        {
            deviceList->addItem(dev->getDeviceTypeName());
        }
    }
    // Get devices from platform directly
    struct { BusType bus; const char *parent; } buses[] = {
        // TODO: enable this after adding default device introspection
        //{ BusType::System, "sys-bus-device" },
        { BusType::IDE, "ide-device" },
        { BusType::PCI, "pci-device" },
    };
    for (auto b : buses)
    {
        if (device->providesBus() == b.bus)
        {
            PlatformInfo pi(device->getPathToConfig());
            foreach(auto dev, pi.getDevices())
            {
                if (dev.getParent() == b.parent)
                {
                    deviceList->addItem(dev.getName());
                    Device *d = new DeviceConfiguration(dev.getName(), NULL);
                    d->setPathToConfig(device->getPathToConfig());
                    addDevices.append(d);
                }
            }
        }
    }

    pWidget = parent;
}

AddDeviceForm::~AddDeviceForm()
{
    foreach(auto dev, addDevices)
    {
        delete dev;
    }
}

int AddDeviceForm::getAddDevicesCount()
{
    return deviceList->count();
}

void AddDeviceForm::addNewDeviceDblClick(QListWidgetItem *item)
{
    addNewDevice();
}

void AddDeviceForm::addDevice()
{
    deviceList->setCurrentRow(0);
    show();
    QemuGUI::setWindowGeometry(this, pWidget);
}

void AddDeviceForm::addNewDevice()
{
    Device *newDevice = addDevices.at(deviceList->currentRow());
    addDevices.removeOne(newDevice);
    emit deviceWantsToAdd(newDevice);
    close();
}

