#ifndef DEVICENETWORK_H
#define DEVICENETWORK_H

#include "Device.h"


class DeviceNetworkController : public Device
{
public:
    static const char typeName[];

    DeviceNetworkController();
    DeviceNetworkController(const QString &n, Device *parent);
    ~DeviceNetworkController() {}

    virtual QString getDeviceTypeName() const { return typeName; }
    virtual BusType needsBus() const { return BusType::PCI; }
#ifdef GUI
    virtual QWidget *getEditorForm();
#endif

    const QStringList getControllers() const;
    const QStringList &getNetdevBackend() const;
    void setController(const QString &name) { controller = name; }
    void setNetdev(const QString &name) { netdev = name; }
    void setTapIfName(const QString &name) { tapIfName = name; }
    QString getCurrentController() const { return controller; }
    QString getCurrentNetdev() const { return netdev; }
    QString getCurrentTabIfName() const { return tapIfName; }

protected:
    virtual QString getCommandLineOption(CommandLineParameters &cmdParams);
    virtual void saveParameters(QXmlStreamWriter &xml) const;
    virtual void readParameters(QXmlStreamReader &xml);
    virtual QString getDeviceInfo();

private:
    void initDefault();
    static const char deviceName[];
    QString controller;
    QString netdev;
    QString tapIfName;

};


#endif // DEVICENETWORK_H


