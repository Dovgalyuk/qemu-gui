#include "CommandLineParameters.h"

LaunchMode CommandLineParameters::getLaunchMode()
{
    return mode;
}

QString CommandLineParameters::getNextOverlayName()
{
    return overlayPath + "/overlay" + QString::number(diskID++) + ".ovl";
}

QString CommandLineParameters::getOverlayForImage(const QString &image)
{
    if (overlayEnabled)
    {
        images.append(image);
        overlays.append(getNextOverlayName());
        return overlays.back();
    }
    else
    {
        return image;
    }
    
}

QString CommandLineParameters::getDriveOption(const QString &image, const QString &id)
{
    if (getLaunchMode() == LaunchMode::NORMAL)
    {
        QString cmdFile = " -drive file=\"" + image + "\"" + ",if=none,id="
            + id + "-drive";
        return cmdFile;
    }
    else
    {
        QString overlay = getOverlayForImage(image);
        QString cmdFile = " -drive file=\"" + overlay + "\"" + ",if=none,id="
            + id + "-file";
        QString overlayEnabled = isOverlayEnabled() ? "" : ",snapshot=on";

        return cmdFile + overlayEnabled + " -drive driver=blkreplay,if=none,image="
            + id + "-file,id=" + id + "-drive";
    }
}
