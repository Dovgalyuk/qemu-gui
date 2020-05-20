#include "DeviceInfo.h"

static const QString xml_device = "Device";
static const QString xml_name = "Name";
static const QString xml_parent = "Parent";
static const QString xml_property = "Property";
static const QString xml_type = "Type";
static const QString xml_description = "Description";

DeviceInfo::DeviceInfo(QXmlStreamReader &xml)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == xml_device);

    // skip the characters
    xml.readNext();

    while (xml.readNext() == QXmlStreamReader::StartElement)
    {
        if (xml.name() == xml_name)
        {
            name = xml.readElementText();
            xml.readNext();
        }
        else if (xml.name() == xml_parent)
        {
            parent = xml.readElementText();
            xml.readNext();
        }
        else if (xml.name() == xml_property)
        {
            xml.readNextStartElement();
            Q_ASSERT(xml.name() == xml_name);
            QString n = xml.readElementText();
            Property p;
            xml.readNextStartElement();
            Q_ASSERT(xml.name() == xml_type);
            p.type = xml.readElementText();
            xml.skipCurrentElement();
            if (xml.readNext() == QXmlStreamReader::StartElement)
            {
                Q_ASSERT(xml.name() == xml_description);
                p.description = xml.readElementText();
                xml.readNext();
                xml.readNext();
            }
            props.insert(n, p);
        }
    }
}

DeviceInfo::DeviceInfo(const QString &n, const QString &p,
    const QJsonArray &json)
    : name(n), parent(p)
{
    for (const QJsonValue &v : json)
    {
        QString name = v.toObject()["name"].toString();
        QString type = v.toObject()["type"].toString();
        QString desc = v.toObject()["description"].toString();

        props.insert(name, {type, desc});
    }
}

void DeviceInfo::serialize(QXmlStreamWriter &xmlWriter) const
{
    xmlWriter.writeStartElement("Device");
        xmlWriter.writeStartElement(xml_name);
            xmlWriter.writeCharacters(name);
        xmlWriter.writeEndElement();
        if (!parent.isEmpty())
        {
            xmlWriter.writeStartElement(xml_parent);
                xmlWriter.writeCharacters(parent);
            xmlWriter.writeEndElement();
        }
        foreach(QString name, props.keys())
        {
            xmlWriter.writeStartElement(xml_property);
                xmlWriter.writeStartElement(xml_name);
                    xmlWriter.writeCharacters(name);
                xmlWriter.writeEndElement();
                xmlWriter.writeStartElement(xml_type);
                    xmlWriter.writeCharacters(props[name].type);
                xmlWriter.writeEndElement();
                if (!props[name].description.isEmpty())
                {
                    xmlWriter.writeStartElement(xml_description);
                    xmlWriter.writeCharacters(props[name].description);
                    xmlWriter.writeEndElement();
                }
            xmlWriter.writeEndElement();
        }
    xmlWriter.writeEndElement();
}
