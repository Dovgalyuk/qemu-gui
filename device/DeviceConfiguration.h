#ifndef DEVICECONFIGURATION_H
#define DEVICECONFIGURATION_H

#include "Device.h"
#include "config/DeviceInfo.h"

/* Device configured through the PlatformInfo/DeviceInfo */
class DeviceConfiguration : public Device
{
public:
    static const char typeName[];

    DeviceConfiguration();
    DeviceConfiguration(const QString &n, Device *parent);

    virtual QString getDeviceTypeName() const { return typeName; }

    DeviceInfo getPlatformDeviceInfo() const;
    void setProperty(const QString &name, const QString &val);
    QString getProperty(const QString &name) const;

protected:
    virtual QString getCommandLineOption(CommandLineParameters &cmdParams);
    virtual QString getDeviceInfo();
    virtual void saveParameters(QXmlStreamWriter &xml) const;
    virtual void readParameters(QXmlStreamReader &xml);

#ifdef GUI
    virtual QWidget *getEditorForm();
#endif

private:
    QMap<QString, QString> props;
};

#endif
