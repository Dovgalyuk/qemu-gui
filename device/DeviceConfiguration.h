#ifndef DEVICECONFIGURATION_H
#define DEVICECONFIGURATION_H

#include "Device.h"

/* Device configured through the PlatformInfo/DeviceInfo */
class DeviceConfiguration : public Device
{
public:
    static const char typeName[];

    DeviceConfiguration();
    DeviceConfiguration(const QString &n, Device *parent);

    virtual QString getDeviceTypeName() const { return typeName; }

protected:
    virtual QString getCommandLineOption(CommandLineParameters &cmdParams);
    virtual QString getDeviceInfo();

#ifdef GUI
    virtual QWidget *getEditorForm();
#endif
};

#endif
