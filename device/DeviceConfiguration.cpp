#include "DeviceConfiguration.h"
#include "DeviceFactory.h"
#ifdef GUI
#include "DeviceForm.h"
#endif
#include "CommandLineParameters.h"
#include "PlatformInfo.h"

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
    return new DeviceForm(this);
}
#endif

QString DeviceConfiguration::getCommandLineOption(CommandLineParameters &cmdParams)
{
    return " -device " + getName() + ",id=" + getId();
}

QString DeviceConfiguration::getDeviceInfo()
{
    return "Device: " + getName() + "\n";
}
