#ifndef PLATFORMINFORMATION_H
#define PLATFORMINFORMATION_H

#include <QtCore/QtCore>

#include "DeviceInfo.h"

class PlatformInfo
{
public:
    typedef QMap<QString, DeviceInfo> Devices;
public:
    explicit PlatformInfo(const QString &path);

    const QStringList &getMachines() const { return machines; }
    const QStringList &getCpus() const { return cpus; }
    const QStringList &getNetdev() const { return netdev; }
    const QStringList &getDrives() const { return drives; }
    const Devices &getDevices() const { return devices; }

    void addMachine(const QString &s, bool isDefault = false);
    void addCpu(const QString &s);
    void addNetdev(const QString &s);
    void addDrive(const QString &s);

    void addDevice(const QString &name, const QString &parent, const QJsonArray &props);

    void saveXml() const;

private:
    QString path;
    QStringList machines;
    QStringList cpus;
    QStringList netdev;
    QStringList drives;

    Devices devices;
};


#endif // PLATFORMINFORMATION_H

