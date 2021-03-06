#ifndef ADDDEVICEFORM_H
#define ADDDEVICEFORM_H

#include <QtWidgets>
#include "Device.h"
#include <QMap>

class AddDeviceForm : public QWidget
{
    Q_OBJECT

public:
    AddDeviceForm(const Device *device, QWidget *parent);
    ~AddDeviceForm();

    int getAddDevicesCount();

public slots:
    void addDevice();

private:
    QWidget *pWidget;
    QListWidget *deviceList;
    Devices addDevices;
    

private slots:
    void addNewDevice();
    void addNewDeviceDblClick(QListWidgetItem *item);

signals:
    void deviceWantsToAdd(Device *);


};

#endif // ADDDEVICEFORM_H
