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
    explicit DeviceInfo(const QString &p, const QJsonArray &json);

    void serialize(QXmlStreamWriter &xmlWriter) const;

private:
    // TODO: name, platform ?
    QString parent;
    QMap<QString, Property> props;
};

#endif
