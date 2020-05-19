#include "DeviceInfo.h"

DeviceInfo::DeviceInfo(const QJsonArray &json)
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
    xmlWriter.writeStartElement("Properties");
    foreach(QString name, props.keys())
    {
        xmlWriter.writeStartElement(name);
            xmlWriter.writeStartElement("Type");
                xmlWriter.writeCharacters(props[name].type);
            xmlWriter.writeEndElement();
            if (!props[name].description.isEmpty())
            {
                xmlWriter.writeStartElement("Description");
                xmlWriter.writeCharacters(props[name].description);
                xmlWriter.writeEndElement();
            }
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
}
