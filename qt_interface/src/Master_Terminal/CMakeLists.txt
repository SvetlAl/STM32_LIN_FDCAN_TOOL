cmake_minimum_required(VERSION 3.5)

#Project Name
project(Master_Terminal VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (ANDROID)
    include(src/android_openssl-master/CMakeLists.txt)
endif()




# This finds QT_VERSION_MAJOR
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)
find_package(Qt6 REQUIRED COMPONENTS SvgWidgets)
find_package(Qt6 REQUIRED COMPONENTS StateMachine)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)
find_package(Qt6 REQUIRED COMPONENTS Core5Compat)
#find_package(Qt6 REQUIRED COMPONENTS CorePrivate)


#я тут делал
#list(APPEND QML_DIRS "C:/Qt/Tools/QtDesignStudio/qt6_design_studio_reduced_version/qml")
#list(APPEND QML_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/content)
#add_subdirectory(content)


# Now PROJECT_SOURCES is the variable, that holds source files
set(PROJECT_SOURCES
        src/main.h
        src/main.cpp
        src/app_settings.h
        src/engine/Obj_list_model.h

        src/core/Core.h
        src/core/Core.cpp
        src/core/CoreStatus.h
        src/core/CoreStatus.cpp
        src/core/Console.h
        src/core/Console.cpp
        src/core/Version.h
        src/core/Version.cpp
        src/core/VersionManager.h
        src/core/VersionManager.cpp

        src/core/design/Appdesign.h
        src/core/design/Appdesign.cpp
        src/core/design/Containerdesign.h
        src/core/design/Containerdesign.cpp

        src/core/user_profile/Userprofile.h
        src/core/user_profile/Userprofile.cpp
        src/core/user_profile/PhoneNumber.h
        src/core/user_profile/PhoneNumber.cpp

        src/engine/file_manager/FileManager.h
        src/engine/file_manager/FileManager.cpp
        src/engine/file_manager/QClassLoader.h
        src/engine/file_manager/QClassLoader.cpp

        src/engine/serial_port/SerialConfig_Preset.h
        src/engine/serial_port/SerialConfig_Preset.cpp
        src/engine/serial_port/QSerialPortConfigItem.h
        src/engine/serial_port/QSerialPortConfigItem.cpp
        src/engine/serial_port/QSerialPortConfigProperty.h
        src/engine/serial_port/QSerialPortConfigProperty.cpp
        src/engine/serial_port/QSerialPortConfig.h
        src/engine/serial_port/QSerialPortConfig.cpp
        src/engine/serial_port/QSerialPortConfigPC.h
        src/engine/serial_port/QSerialPortConfigPC.cpp
        src/engine/serial_port/QSerialPortConfigJNI.h
        src/engine/serial_port/QSerialPortConfigJNI.cpp

        src/engine/serial_port/CDC_Driver.h
        src/engine/serial_port/CDC_Driver.cpp
        src/engine/serial_port/CDC_JNI_Driver.h
        src/engine/serial_port/CDC_JNI_Driver.cpp
        src/engine/serial_port/CDC_PC_Driver.h
        src/engine/serial_port/CDC_PC_Driver.cpp

        src/engine/command_manager/CommandConstructor.h
        src/engine/command_manager/CommandConstructor.cpp
        src/engine/command_manager/CommandManager.h
        src/engine/command_manager/CommandManager.cpp
        src/engine/command_manager/StringConvertor.h
        src/engine/command_manager/StringConvertor.cpp
        src/engine/command_manager/Command.h
        src/engine/command_manager/Command.cpp

        src/engine/translator/Qmltranslator.h
        src/engine/translator/Qmltranslator.cpp

        src/engine/memory/MemoryTablemodel.h
        src/engine/memory/MemoryTablemodel.cpp
        src/engine/memory/MemoryManager.h
        src/engine/memory/MemoryManager.cpp
        src/engine/memory/MemoryDataProperty.h
        src/engine/memory/MemoryDataProperty.cpp
        src/engine/memory/MemoryDataItem.h
        src/engine/memory/MemoryDataItem.cpp

        src/engine/stm32_device/DeviceManager.h
        src/engine/stm32_device/DeviceManager.cpp
        src/engine/stm32_device/OverrideStatus.h
        src/engine/stm32_device/OverrideStatus.cpp
        src/engine/stm32_device/QML_Model/QDiscardId_ModelItem.h
        src/engine/stm32_device/QML_Model/QDiscardId_ModelItem.cpp
        src/engine/stm32_device/QML_Model/QDiscardId_ModelProperty.h
        src/engine/stm32_device/QML_Model/QDiscardId_ModelProperty.cpp
        src/engine/stm32_device/QML_Model/QOverrideFilter_ModelItem.h
        src/engine/stm32_device/QML_Model/QOverrideFilter_ModelItem.cpp
        src/engine/stm32_device/QML_Model/QOverrideFilter_ModelProperty.h
        src/engine/stm32_device/QML_Model/QOverrideFilter_ModelProperty.cpp

        src/engine/stm32_device/QML_Model/QLinConfigItem.h
        src/engine/stm32_device/QML_Model/QLinConfigItem.cpp
        src/engine/stm32_device/QML_Model/QLinConfigProperty.h
        src/engine/stm32_device/QML_Model/QLinConfigProperty_BaudRate.h
        src/engine/stm32_device/QML_Model/QLinConfigProperty_FilterPreset.h
        src/engine/stm32_device/QML_Model/QLinOverrideFilter_ModelItem.h
        src/engine/stm32_device/QML_Model/QLinOverrideFilter_ModelItem.cpp
        src/engine/stm32_device/QML_Model/QLinOverrideFilter_ModelProperty.h
        src/engine/stm32_device/QML_Model/QLinOverrideFilter_ModelProperty.cpp
        src/engine/stm32_device/Lin_filter.h


        src/engine/vehicle/Vehicle.h
        src/engine/vehicle/Vehicle.cpp
        src/engine/vehicle/QML_Model/QVehicle_ModelItem.h
        src/engine/vehicle/QML_Model/QVehicle_ModelItem.cpp
        src/engine/vehicle/QML_Model/QVehicle_ModelProperty.h
        src/engine/vehicle/QML_Model/QVehicle_ModelProperty.cpp

        src/engine/web/WebManager.h
        src/engine/web/WebManager.cpp
        src/engine/web/WebConfig_Preset.h
        src/engine/web/WebConfig_Preset.cpp
        src/engine/web/WebConfig.h
        src/engine/web/WebConfig.cpp
        src/engine/web/Downloader.h
        src/engine/web/Downloader.cpp

        src/engine/androidserial/QASerialPort.cpp
        src/engine/androidserial/QASerialPort.h
        src/engine/androidserial/QASerialPortinfo.cpp
        src/engine/androidserial/QASerialPortinfo.h

        src/engine/bus/BusManager.h
        src/engine/bus/BusManager.cpp
        src/engine/bus/BusDataProperty.h
        src/engine/bus/BusDataProperty.cpp
        src/engine/bus/CanBusItem.h
        src/engine/bus/CanBusItem.cpp
        src/engine/bus/LinBusItem.h
        src/engine/bus/LinBusItem.cpp
        src/engine/bus/LinBusDataProperty.h
        src/engine/bus/LinBusDataProperty.cpp
        src/engine/bus/ParseFilter.h
        src/engine/bus/ParseBuffer.h
        src/engine/bus/ParseBuffer.cpp



        src/resources.rc
    )

set(PROJECT_RESOURCES
        android/AndroidManifest.xml
        android/gradle.properties
        android/build.gradle

        MasterTerminal.qrc
        Languages.qrc)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    enable_language("RC")
    set (WIN32_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/resources.rc)
endif()


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Master_Terminal MANUAL_FINALIZATION ${WIN32_RESOURCES} ${PROJECT_SOURCES} ${PROJECT_RESOURCES})

# Define target properties for Android with Qt 6 as:
set_property(TARGET Master_Terminal APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
                 ${CMAKE_CURRENT_SOURCE_DIR}/android)

set_property(TARGET Master_Terminal PROPERTY QT_ANDROID_EXTRA_LIBS
                 ${CMAKE_CURRENT_SOURCE_DIR}/src/android_openssl-master/latest/arm/libcrypto_1_1.so
                 ${CMAKE_CURRENT_SOURCE_DIR}/src/android_openssl-master/latest/arm/libssl_1_1.so)

# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Master_Terminal SHARED
            ${PROJECT_SOURCES})




 #   set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Master_Terminal ${PROJECT_SOURCES})
    endif()
endif()

# Link QT libraries with executable file
target_link_libraries(Master_Terminal PRIVATE Qt6::Widgets)
target_link_libraries(Master_Terminal PRIVATE Qt6::SvgWidgets)
target_link_libraries(Master_Terminal PRIVATE Qt6::StateMachine)
target_link_libraries(Master_Terminal PUBLIC  Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick)
target_link_libraries(Master_Terminal PRIVATE Qt6::SerialPort)
target_link_libraries(Master_Terminal PRIVATE Qt6::CorePrivate)
target_link_libraries(Master_Terminal PRIVATE Qt6::Core5Compat)


#target_link_libraries(Master_Terminal PRIVATE contentplugin)

set_target_properties(Master_Terminal PROPERTIES
  #  MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Master_Terminal)
endif()






# set(QML_IMPORT_PATH "${QML_DIRS}" CACHE STRING "")
#add_subdirectory(QML_interface/content)
#add_subdirectory(QML_interface/imports)


