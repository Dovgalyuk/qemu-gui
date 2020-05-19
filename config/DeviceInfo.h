#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QtCore/QtCore>

class DeviceInfo
{
public:
    struct Property
    {
        QString type;
        QString description;
    };
public:
    DeviceInfo() {}
    explicit DeviceInfo(const QJsonArray &json);

    void serialize(QXmlStreamWriter &xmlWriter) const;

private:
    // TODO: name, platform ?
    QMap<QString, Property> props;
};

#endif
