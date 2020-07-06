#include "VMConfig.h"
#include "device/DeviceBus.h"
#include "device/DeviceStorage.h"
#include "device/DeviceSystem.h"
#include "device/DeviceUsb.h"
#include "common/FileHelpers.h"

const QString const_xml_name = "vm.xml";
const QString xml_parameters = "VMParameters";
const QString xml_field_name = "Name";
const QString xml_field_dir = "Directory_path";
const QString xml_field_img = "Image_path";
const QString xml_platform = "Platform";
const QString xml_cmdLine = "AdditionCommandLine";
const QString xml_kernel = "Kernel";
const QString xml_initrd = "InitialRamDisk";


VMConfig::VMConfig(const QString &path_vm)
    : system("System")
{
    list_of_vm_file = NULL;
    system.setRemovable(false);
    path = path_vm;
    QString xml_name;
    if (path_vm.section('/', -1) != const_xml_name)
    {
        dir_path = path;
        path = path + "/" + const_xml_name;
    }
    else
    {
        dir_path = path;
        dir_path.chop(const_xml_name.size());
    }

    readVMConfig();
}

VMConfig::~VMConfig()
{

}

void VMConfig::createVMFolder(const QString &path) const
{
    QDir vm_dir(path);
    if (!vm_dir.exists())
    {
        QDir().mkdir(path);
    }
}

void VMConfig::readVMConfig()
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader xmlReader(&file);

        xmlReader.readNextStartElement();
        Q_ASSERT(xmlReader.name() == xml_parameters);

        while (xmlReader.readNextStartElement())
        {
            if (xmlReader.name() == xml_field_name)
            {
                name_vm = xmlReader.readElementText();
            }
            else if (xmlReader.name() == xml_platform)
            {
                platform = xmlReader.readElementText();
            }
            else if (xmlReader.name() == xml_cmdLine)
            {
                addCmdLine = xmlReader.readElementText();
            }
            else if (xmlReader.name() == xml_kernel)
            {
                kernel = xmlReader.readElementText();
            }
            else if (xmlReader.name() == xml_initrd)
            {
                initrd = xmlReader.readElementText();
            }
            else /* Device */
            {
                system.read(xmlReader);
            }
        }
    }
    else
    {
        /* Default config */
    }
}

bool VMConfig::save_vm_config(const QString &path) const
{
    createVMFolder(path);

    QString xml_name;
    xml_name = path + "/" + const_xml_name;

    QFile file(xml_name);
    if (file.open(QIODevice::WriteOnly))
    {
        QXmlStreamWriter xmlWriter(&file);

        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement(xml_parameters);

        xmlWriter.writeStartElement(xml_field_name);
        xmlWriter.writeCharacters(name_vm);
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement(xml_platform);
        xmlWriter.writeCharacters(platform);
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement(xml_cmdLine);
        xmlWriter.writeCharacters(addCmdLine);
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement(xml_kernel);
        xmlWriter.writeCharacters(kernel);
        xmlWriter.writeEndElement();

        xmlWriter.writeStartElement(xml_initrd);
        xmlWriter.writeCharacters(initrd);
        xmlWriter.writeEndElement();

        system.save(xmlWriter);

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        file.close();
        return true;
    }
    return false;
}

void VMConfig::save_vm_config() const
{
    save_vm_config(dir_path);
}

void VMConfig::set_name(const QString &name_vm_)
{
    name_vm = name_vm_;
}

void VMConfig::setCmdLine(const QString &cmdLine)
{
    addCmdLine = cmdLine;
}

void VMConfig::addDefaultBus(const QString &image)
{
    Device *pci = new DevicePciController(&system);
    pci->setRemovable(false);
    Device *ide = new DeviceIdeController(pci->getDevices().at(0));
    ide->setRemovable(false);
    if (!image.isEmpty())
    {
        new DeviceIdeHd(image, ide->getDevices().at(0));
    }
    // system bus for user devices
    // TODO: Will be enabled later
    //new DeviceBusSystem(&system);
}

void VMConfig::addDeviceMemory(const QString &size)
{
    (new DeviceMemory(size, &system))->setRemovable(false);
}

void VMConfig::addDeviceMachine(const QString &name)
{
    (new DeviceMachine(name, &system))->setRemovable(false);
}

void VMConfig::addDeviceCpu(const QString &name)
{
    (new DeviceCpu(name, &system))->setRemovable(false);
}

void VMConfig::setKernel(const QString &name)
{
    kernel = name;
}

void VMConfig::setInitrd(const QString &name)
{
    initrd = name;
}

void VMConfig::addUsbDevice()
{
    qDebug() << "---usb" << (new DeviceUsb(&system))->getDeviceTypeName();
    //save_vm_config();
}

QString VMConfig::get_vm_info()
{
    QString info = "Name: " + name_vm + "\n" + "Directory: " + dir_path + "\n" + 
        "Platform: " + platform + "\n";
    QString kernelInfo = (!kernel.isEmpty()) ? "Kernel: " + kernel + "\n" : "";
    QString initrdInfo = (!initrd.isEmpty()) ? "Initial ram disk: " + initrd + "\n" : "";
    info += (kernelInfo + initrdInfo);
    info += system.getCommonDeviceInfo();
    return info;
}

void VMConfig::setPlatform(const QString &platformVM)
{
    platform = platformVM;
}

QString VMConfig::getPlatform()
{
    return platform;
}

QString VMConfig::getMachine()
{
    foreach(Device *dev, system.getDevices())
    {
        if (dev->getDeviceTypeName() == "DeviceMachine")
        {
            DeviceMachine *machine = dynamic_cast<DeviceMachine *>(dev);
            return machine->getName();
        }
    }
    return "";
}

QString VMConfig::get_name()
{
    return name_vm;
}

QString VMConfig::getKernel()
{
    return kernel;
}

QString VMConfig::getInitrd()
{
    return initrd;
}

QString VMConfig::getCmdLine()
{
    return addCmdLine;
}

QString VMConfig::get_dir_path()
{
    return dir_path;
}

QString VMConfig::getCommandLine(CommandLineParameters &cmdParams)
{
    return QString(" -net none")
        + (kernel.isEmpty() ? "" : " -kernel " + kernel)
        + (initrd.isEmpty() ? "" : " -initrd " + initrd)
        + system.getCommandLine(cmdParams) + " " + addCmdLine;
}

QString VMConfig::getPathRRDir()
{
    return get_dir_path() + "/RecordReplay";
}

RecordReplayParams VMConfig::getRRParams(const QString &exec)
{
    RecordReplayParams params;
    params.setCurrentDir(getPathRRDir() + "/" + exec);
    params.readXml();
    return params;
}

void VMConfig::remove_directory_vm()
{
    FileHelpers::deleteDirectory(dir_path);
}

QStringList VMConfig::getReplayList()
{
    QDir rrDir(getPathRRDir());
    QStringList dirs = rrDir.entryList(QDir::Dirs | QDir::AllDirs | QDir::Filter::NoDotAndDotDot);
    return dirs;
}
