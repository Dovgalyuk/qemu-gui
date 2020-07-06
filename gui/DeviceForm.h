#ifndef DEVICEFORM_H
#define DEVICEFORM_H

#include <QtWidgets>
#include "device/DeviceStorage.h"
#include "device/DeviceSystem.h"
#include "device/DeviceNetwork.h"
#include "device/DeviceConfiguration.h"

class DeviceCommandLineForm;

class DeviceForm : public QGroupBox
{
    Q_OBJECT

public:
    DeviceForm(Device *dev);
    DeviceCommandLineForm *getCmdWidget() { return cmdWidget; }

protected:
    void devFormAddWidget(QWidget *widget);
    void devFormAddLayout(QLayout *layout);

private:
    Device *device;
    QVBoxLayout *mainLay;
    DeviceCommandLineForm *cmdWidget;
};

class DriveSelector : public QHBoxLayout
{
    Q_OBJECT
public:
    DriveSelector(const QString &image);
signals:
    void diskSelected(const QString &image);
};

class DeviceStorageForm : public DeviceForm
{
    Q_OBJECT

public:
    DeviceStorageForm(DeviceStorage *dev);

private:
    DeviceStorage *device;
};


class DeviceScsiControllerForm : public DeviceForm
{
    Q_OBJECT

public:
    DeviceScsiControllerForm(DeviceScsiController *dev);

private:
    DeviceScsiController *device;

private slots:
    void setController(const QString &name);

};


class DeviceCommandLineForm : public QGroupBox
{
    Q_OBJECT

public:
    DeviceCommandLineForm(Device *dev);
    void updateCmd();

private:
    Device *device;
    QTextEdit *cmdLine;
    QLabel *optionalLbl;
    QLineEdit *optionalLine;

private slots:
    void showCmdLine();
    void saveUserOptions();
};


class DeviceMemoryForm : public DeviceForm
{
    Q_OBJECT

public:
    DeviceMemoryForm(DeviceMemory *dev);

private:
    DeviceMemory *device;

    private slots:
    void sizeChanged(int val);
};


class DeviceNetworkForm : public DeviceForm
{
    Q_OBJECT

public:
    DeviceNetworkForm(DeviceNetworkController *dev);

private:
    DeviceNetworkController *device;
    QLineEdit *tapIfNameEdit;
    QComboBox *netdevCombo;
    QLabel *tapIfNameLbl;

    void setVisibleTapSetting();

private slots:
    void setController(const QString &name);
    void setNetdev(const QString &name);
    void setTapIfName();

};

class DeviceCpuForm : public DeviceForm
{
    Q_OBJECT

public:
    DeviceCpuForm(DeviceCpu *dev);

private:
    DeviceCpu *device;
};

class DeviceConfigurationForm : public DeviceForm
{
    Q_OBJECT

public:
    DeviceConfigurationForm(DeviceConfiguration *dev);

private:
    DeviceConfiguration *device;
};

#endif // DEVICEFORM_H
