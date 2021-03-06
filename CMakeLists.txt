cmake_minimum_required(VERSION 3.1.0)

project(qemu-gui)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Network)

include_directories(gui device config qemu)

add_executable(qemu-gui
    common/FileHelpers.cpp

    config/GlobalConfig.cpp config/VMConfig.cpp config/PlatformInfo.cpp 
    config/RecordReplayParams.cpp config/QemuList.cpp config/DeviceInfo.cpp

    device/Device.cpp device/DeviceBus.cpp device/DeviceStorage.cpp
    device/DeviceFactory.cpp device/DeviceSystem.cpp
    device/DeviceUsb.cpp device/DeviceNetwork.cpp
    device/DeviceConfiguration.cpp

    qemu/QemuRunOptions.cpp qemu/QemuLauncher.cpp qemu/QemuImgLauncher.cpp
    qemu/CommandLineParameters.cpp qemu/QMPInteraction.cpp
    qemu/PlatformInformationReader.cpp qemu/QemuSocket.cpp

    gui/main.cpp gui/CreateVMForm.cpp gui/QemuGUI.cpp
    gui/RecordReplayTab.cpp gui/VMSettingsForm.cpp gui/QemuGUI.qrc
    gui/TerminalSettingsForm.cpp
    gui/TerminalTab.cpp gui/ConnectionSettingsForm.cpp
    gui/ConsoleTab.cpp
    gui/VMPropertiesForm.cpp
    gui/AddDeviceForm.cpp
    gui/DeviceForm.cpp gui/QemuInstallationsForm.cpp
    )

target_link_libraries(qemu-gui Qt5::Widgets Qt5::Network)
target_compile_definitions(qemu-gui PUBLIC GUI)


add_executable(qemu-cli cli/main.cpp
    common/FileHelpers.cpp

    config/GlobalConfig.cpp config/VMConfig.cpp config/QemuList.cpp
    config/PlatformInfo.cpp config/RecordReplayParams.cpp config/DeviceInfo.cpp

    device/Device.cpp device/DeviceBus.cpp device/DeviceStorage.cpp device/DeviceSystem.cpp
    device/DeviceUsb.cpp device/DeviceNetwork.cpp device/DeviceFactory.cpp
    device/DeviceConfiguration.cpp

    qemu/PlatformInformationReader.cpp qemu/QemuRunOptions.cpp qemu/QemuLauncher.cpp
    qemu/QemuImgLauncher.cpp qemu/CommandLineParameters.cpp
    qemu/QMPInteraction.cpp qemu/QemuSocket.cpp
    )
target_link_libraries(qemu-cli Qt5::Core Qt5::Gui Qt5::Network)



install(TARGETS qemu-gui
        RUNTIME DESTINATION bin)
install(TARGETS qemu-cli
        RUNTIME DESTINATION bin)
