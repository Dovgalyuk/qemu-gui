#include "PlatformInfo.h"


PlatformInfo::PlatformInfo(const QString &path)
    : path(path)
{
    QFile file(path + ".xml");
    if (file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader xmlReader(&file);
        xmlReader.readNextStartElement();

        while (xmlReader.readNextStartElement())
        {
            if (xmlReader.name() == "Machine")
            {
                machines.append(xmlReader.readElementText());
            }
            else if (xmlReader.name() == "Cpu")
            {
                cpus.append(xmlReader.readElementText());
            }
            else if (xmlReader.name() == "Netdev")
            {
                netdev.append(xmlReader.readElementText());
            }
            else if (xmlReader.name() == "Drive")
            {
                drives.append(xmlReader.readElementText());
            }
        }
    }
}

void PlatformInfo::addMachine(const QString &s, bool isDefault)
{
    if (isDefault)
    {
        machines.push_front(s);
    }
    else
    {
        machines.append(s);
    }
}

void PlatformInfo::addCpu(const QString &s)
{
    cpus.append(s);
}

void PlatformInfo::addNetdev(const QString &s)
{
    netdev.append(s);
}

void PlatformInfo::addDrive(const QString &s)
{
    drives.append(s);
}

void PlatformInfo::addDevice(const QString &name, const QJsonArray &props)
{
    devices.insert(name, DeviceInfo(props));
}

void PlatformInfo::saveXml() const
{
    QFile file(path + ".xml");
    if (file.open(QIODevice::WriteOnly))
    {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("Platform");

        foreach(QString name, machines)
        {
            xmlWriter.writeStartElement("Machine");
            xmlWriter.writeCharacters(name);
            xmlWriter.writeEndElement();
        }

        xmlWriter.writeStartElement("Cpu");
        xmlWriter.writeCharacters("default");
        xmlWriter.writeEndElement();

        foreach(QString name, cpus)
        {
            xmlWriter.writeStartElement("Cpu");
            xmlWriter.writeCharacters(name);
            xmlWriter.writeEndElement();
        }

        foreach(QString name, netdev)
        {
            xmlWriter.writeStartElement("Netdev");
            xmlWriter.writeCharacters(name);
            xmlWriter.writeEndElement();
        }

        foreach(QString name, drives)
        {
            xmlWriter.writeStartElement("Drive");
            xmlWriter.writeCharacters(name);
            xmlWriter.writeEndElement();
        }

        foreach(QString name, devices.keys())
        {
            xmlWriter.writeStartElement("Device");
                xmlWriter.writeStartElement("Name");
                    xmlWriter.writeCharacters(name);
                xmlWriter.writeEndElement();
                devices[name].serialize(xmlWriter);
            xmlWriter.writeEndElement();
        }

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
    }
}
