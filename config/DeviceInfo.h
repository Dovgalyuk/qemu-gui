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
    explicit DeviceInfo(QXmlStreamReader &xml);
    DeviceInfo(const QString &n, const QString &p,
        const QJsonArray &json);

    const QString &getName() const { return name; }
    const QString &getParent() const { return parent; }

    void serialize(QXmlStreamWriter &xmlWriter) const;

private:
    // TODO: platform ?
    QString name;
    QString parent;
    QMap<QString, Property> props;
};

#endif
