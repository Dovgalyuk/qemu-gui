#ifndef PLATFORMINFORMATION_H
#define PLATFORMINFORMATION_H

#include <QtCore/QtCore>

class PlatformInfo
{
public:
    explicit PlatformInfo(const QString &path);

    const QStringList &getMachines() const { return machines; }
    const QStringList &getCpus() const { return cpus; }
    const QStringList &getNetdev() const { return netdev; }
    const QStringList &getDrives() const { return drives; }

    void addMachine(const QString &s, bool isDefault = false);
    void addCpu(const QString &s);
    void addNetdev(const QString &s);
    void addDrive(const QString &s);

    void saveXml() const;

private:
    QString path;
    QStringList machines;
    QStringList cpus;
    QStringList netdev;
    QStringList drives;
};


#endif // PLATFORMINFORMATION_H

