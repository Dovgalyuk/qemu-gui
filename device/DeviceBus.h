#ifndef DEVICEBUS_H
#define DEVICEBUS_H

#include "Device.h"

class DeviceStorageController;
class DeviceIdeController;
class DevicePciController;

class DeviceBus : public Device
{
public:
    DeviceBus(const QString &n, Device *parent);

    virtual QString getDeviceTypeName() const = 0;
    virtual int getMaxCountDevices() const { return 1024; }
};

class DeviceBusSystem : public DeviceBus
{
public:
    static const char typeName[];

    DeviceBusSystem(Device *parent);

    virtual QString getDeviceTypeName() const { return typeName; }

    virtual BusType providesBus() const { return BusType::System; }
private:
};

class DeviceBusIde : public DeviceBus
{
public:
    static const char typeName[];

    DeviceBusIde(int n, DeviceIdeController *parent);

    virtual QString getDeviceTypeName() const { return typeName; }

    virtual BusType providesBus() const { return BusType::IDE; }
    virtual int getMaxCountDevices() const { return 1; }

    int getNumber() const { return num; }
private:
    int num;
};


class DeviceBusPci : public DeviceBus
{
public:
    static const char typeName[];

    DeviceBusPci(int n, DevicePciController *parent);

    virtual QString getDeviceTypeName() const { return typeName; }

    virtual BusType providesBus() const { return BusType::PCI; }

    int getNumber() const { return num; }
private:
    int num;
};

#endif // DEVICEBUS_H
