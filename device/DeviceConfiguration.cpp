#include "DeviceConfiguration.h"
#include "DeviceFactory.h"
#ifdef GUI
#include "DeviceForm.h"
#endif
#include "CommandLineParameters.h"
#include "PlatformInfo.h"

static const QString xml_properties = "Properties";
static const QString xml_property = "Property";
static const QString xml_name = "Name";
static const QString xml_value = "Value";

const char DeviceConfiguration::typeName[] = "DeviceConfiguration";

REGISTER_DEVICE(DeviceConfiguration)


DeviceConfiguration::DeviceConfiguration()
    : Device("", NULL)
{
}

DeviceConfiguration::DeviceConfiguration(const QString &n, Device *parent)
    : Device(n, parent)
{
}

#ifdef GUI
QWidget *DeviceConfiguration::getEditorForm()
{
    return new DeviceConfigurationForm(this);
}
#endif

QString DeviceConfiguration::getCommandLineOption(CommandLineParameters &cmdParams)
{
    QString res = " -device " + getName() + ",id=" + getId();
    foreach (auto name, props.keys())
    {
        res += "," + name + "=" + props[name];
    }
    return res;
}

QString DeviceConfiguration::getDeviceInfo()
{
    return "Device: " + getName() + "\n";
}

void DeviceConfiguration::saveParameters(QXmlStreamWriter &xml) const
{
    xml.writeStartElement(xml_properties);
    foreach (auto name, props.keys())
    {
        xml.writeStartElement(xml_property);
            xml.writeStartElement(xml_name);
                xml.writeCharacters(name);
            xml.writeEndElement();
            xml.writeStartElement(xml_value);
                xml.writeCharacters(props[name]);
            xml.writeEndElement();
        xml.writeEndElement();
    }
    xml.writeEndElement();
}

void DeviceConfiguration::readParameters(QXmlStreamReader &xml)
{
    props.clear();

    xml.readNextStartElement();
    Q_ASSERT(xml.name() == xml_properties);

    while (xml.readNextStartElement())
    {
        Q_ASSERT(xml.name() == xml_property);
        xml.readNextStartElement();
        Q_ASSERT(xml.name() == xml_name);
        QString name = xml.readElementText();
        xml.readNext();

        xml.readNextStartElement();
        Q_ASSERT(xml.name() == xml_value);
        QString value = xml.readElementText();
        xml.readNext();

        props[name] = value;

        xml.readNext();
    }

    xml.readNext();
}

DeviceInfo DeviceConfiguration::getPlatformDeviceInfo() const
{
    PlatformInfo pi(getPathToConfig());
    return pi.getDevices()[getName()];
}

void DeviceConfiguration::setProperty(const QString &name, const QString &val)
{
    if (val.isEmpty())
        props.remove(name);
    else
        props[name] = val;
}

QString DeviceConfiguration::getProperty(const QString &name) const
{
    auto it = props.find(name);
    if (it == props.end())
        return "";
    
    return it.value();
}
