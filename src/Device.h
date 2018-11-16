#ifndef DEVICE_H
#define DEVICE_H

#include <QWidget>
#include <QtWidgets>

class Device;
class CommandLineParameters;

enum class BusType
{
    None,
    System,
    IDE,
    PCI,
};

typedef QList<Device *> Devices;

class Device : public QObject
{
    Q_OBJECT
public:
    Device();
    Device(const QString &n, Device *parent = 0);

    void addDevice(Device *dev);
    void removeDevice(Device *dev);
    const Devices &getDevices() const { return devices; }
    QString getDescription() const;
    QString getCommandLine(CommandLineParameters &cmdParams);

    void save(QXmlStreamWriter &xml) const;
    void read(QXmlStreamReader &xml);

    virtual QString getDeviceTypeName() const { return "Device"; }
    virtual QWidget *getEditorForm() { return NULL; }
    virtual bool isDeviceValid() { return true; }

    virtual BusType providesBus() const { return BusType::None; }
    virtual BusType needsBus() const { return BusType::None; }

    const QString &getId() const { return id; }
protected:
    void setId(const QString &s) { id = s; }

    virtual void saveParameters(QXmlStreamWriter &xml) const {}
    virtual void readParameters(QXmlStreamReader &xml) {}
    virtual QString getCommandLineOption(CommandLineParameters &cmdParams) { return ""; }

private:
    void init();

private:
    QString name;
    // Device id for the command line.
    // Does not need to be saved in the config file.
    QString id;
    Devices devices;
};

#endif // DEVICE_H
