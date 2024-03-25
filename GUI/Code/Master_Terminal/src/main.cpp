/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Quick Studio Components.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QSslSocket>
#include <QProcess>
#include <QTextCodec>


#include "app_environment.h"
#include "app_settings.h"
#include "src/core/Core.h"
#include "src/core/Console.h"
#include "src/core/VersionManager.h"
#include "src/engine/translator/Qmltranslator.h"
#include "src/engine/serial_port/QSerialPortConfig.h"
#include "src/engine/serial_port/QSerialPortConfigPC.h"
#include "src/engine/serial_port/QSerialPortConfigJNI.h"
#include "src/engine/command_manager/CommandManager.h"
#include "src/engine/vehicle/Vehicle.h"
#include "src/engine/web/WebConfig.h"
#include "src/engine/web/WebManager.h"
#include "src/engine/memory/MemoryManager.h"
#include "src/engine/bus/BusManager.h"
#include "src/engine/stm32_device/DeviceManager.h"
#include "src/engine/resource_extractor/PngExtractor.h"


/* Create a core instance */
Core core;

int main(int argc, char *argv[]){
    set_qt_environment();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    /* Init Core: profile, design settings */
    core.init(); // load profile and design settings
    qmlRegisterType<Core>("Core", 1, 0, "Core");
    engine.rootContext()->setContextProperty("core", &core);

    /* Create a translator instance */
    QmlTranslator qmlTranslator;
    engine.rootContext()->setContextProperty("qmlTranslator", &qmlTranslator);
    qmlTranslator.setTranslation(core.getUserProfileValue(UserProfile::ProfileMembers::Language));

    /* Create a QSerialPortConfig, Console and CommandManager instances */
    WebManager *webManager = new WebManager(&app);
    WebConfig *webConfig = new WebConfig(&app);
    VersionManager *versionManager = new VersionManager(&app);
    Console *interface_console = new Console(&app);
    CommandManager *cmd_manager = new CommandManager(&app);
    MemoryManager *memory_manager = new MemoryManager(&app);
    DeviceManager *device_manager = new DeviceManager(&app);
    BusManager *bus_manager = new BusManager(&app);
    cmd_manager->setPConsole(interface_console);
    cmd_manager->setVersions(versionManager);
    cmd_manager->setDeviceManager(device_manager);

    #if defined(PC_WINDOWS) || defined(PC_LINUX)
        QSerialPortConfig *serialport_config = new QSerialPortConfigPC(cmd_manager);
    #elif defined(ANDROID_V)
       QSerialPortConfig *serialport_config = new QSerialPortConfigJNI(cmd_manager);
    #else
        #error "Either PC_V or ANDROID_V must be defined."
    #endif
    cmd_manager->setPSerialPortConfig(serialport_config);


  //  qmlRegisterType<MemoryTablemodel>("MemoryTablemodel", 0, 1, "MemoryTablemodel");
    Vehicle *theVehicle = new Vehicle(&app);

    engine.rootContext()->setContextProperty("bus_manager", bus_manager);
    engine.rootContext()->setContextProperty("device_manager", device_manager);
    engine.rootContext()->setContextProperty("memory_manager", memory_manager);
    engine.rootContext()->setContextProperty("webManager", webManager);
    engine.rootContext()->setContextProperty("webConfig", webConfig);
    engine.rootContext()->setContextProperty("versionManager", versionManager);
    engine.rootContext()->setContextProperty("interface_console", interface_console);
    engine.rootContext()->setContextProperty("cmd_manager", cmd_manager);
    engine.rootContext()->setContextProperty("serialport_config", serialport_config);
    engine.rootContext()->setContextProperty("theVehicle", theVehicle);
    cmd_manager->init_driver(); 

    /* Set cross references */
    cmd_manager->setVehicle(theVehicle);
    cmd_manager->setPMemoryManager(memory_manager);
    webManager->setConsole(interface_console);
    webManager->setWebConfig(webConfig);
    webManager->setVersionManager(versionManager);
    webManager->setCommandManager(cmd_manager);
    versionManager->setConsole(interface_console);
    cmd_manager->setPBusManager(bus_manager);
    core.setWebConfig(webConfig);
    core.setSerialport_config(serialport_config);
    core.loadSerialPortPreset();
    core.loadWebConfigPreset();
    core.setVersionManager(versionManager);


    versionManager->handleDeviceVersionInfo();





    PngExtractor *png_extractor = new PngExtractor(&app);
    engine.rootContext()->setContextProperty("png_extractor", png_extractor);

    FDCAN_injection_message *fdcan_inj_msg = new FDCAN_injection_message(&app);
    engine.rootContext()->setContextProperty("fdcan_inj_msg", fdcan_inj_msg);
    cmd_manager->setPFdcan_inj_msg(fdcan_inj_msg);


    /* Register singletons */
    qmlRegisterSingletonType(QUrl("qrc:/content/CoreImport.qml"), "CoreImport", 1, 0, "CoreImport");

    const QUrl url(u"qrc:/content/App.qml"_qs);
    QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated, &app,
                [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    },
    Qt::QueuedConnection);

    engine.load(url);

    const QUrl url2(u"qrc:/content/CoreImport.qml"_qs);
    engine.load(url2);

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    return app.exec();
}



