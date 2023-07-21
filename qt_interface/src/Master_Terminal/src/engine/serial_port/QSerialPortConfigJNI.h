#ifndef QSERIALPORTCONFIGJNI_H
#define QSERIALPORTCONFIGJNI_H

#include "../../app_settings.h"
#ifdef QT_IN_USE
#include <QDebug>
#endif

#include "QSerialPortConfigProperty.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include "SerialConfig_Preset.h"
#include "QSerialPortConfig.h"
#ifdef ANDROID_V
#include "../androidserial/QASerialPortinfo.h"
#endif



class QSerialPortConfigJNI: public QSerialPortConfig{
    Q_OBJECT

public:
    QSerialPortConfigJNI(QObject *parent = nullptr): QSerialPortConfig(parent){
        m_portnames.clear();
        auto _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, "No_Port", 0));
        m_portnames.append(_item);

#ifdef ANDROID_V
        int value = 1;
        foreach (const QASerialPortInfo &info, QASerialPortInfo::availablePorts()) {
           auto _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, info.portName(), value++));
           m_portnames.append(_item);
        }
        if(value > 1){
            m_portnames.setCurrentIndex(1);
            m_portnames.setDefaultIndex(1);
        }
        else {
            m_portnames.setCurrentIndex(0);
            m_portnames.setDefaultIndex(0);
        }
#endif

        m_baudrate.clear();
        _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, "AndroidJNI", 0));
        m_baudrate.append(_item);
        m_baudrate.setCurrentIndex(0);
        m_baudrate.setDefaultIndex(0);

        m_parity.clear();
        _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, "AndroidJNI", 0));
        m_parity.append(_item);
        m_parity.setCurrentIndex(0);
        m_parity.setDefaultIndex(0);

        m_databits.clear();
        _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, "AndroidJNI", 0));
        m_databits.append(_item);
        m_databits.setCurrentIndex(0);
        m_databits.setDefaultIndex(0);

        m_stopbits.clear();
        _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, "AndroidJNI", 0));
        m_stopbits.append(_item);
        m_stopbits.setCurrentIndex(0);
        m_stopbits.setDefaultIndex(0);

        m_flowcontrol.clear();
        _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, "AndroidJNI", 0));
        m_flowcontrol.append(_item);
        m_flowcontrol.setCurrentIndex(0);
        m_flowcontrol.setDefaultIndex(0);

    };
    ~QSerialPortConfigJNI(){ }

    void refresh_ports() override{
        m_portnames.clear();
        auto _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, "No_Port", 0));
        m_portnames.append(_item);

#ifdef ANDROID_V


        int value = 1;
        foreach (const QASerialPortInfo &info, QASerialPortInfo::availablePorts()) {
           auto _item = QSharedPointer<QSerialPortConfigItem>(new QSerialPortConfigItem(this, info.portName(), value++));
           m_portnames.append(_item);
        }
        if(value > 1){
            m_portnames.setCurrentIndex(1);
            m_portnames.setDefaultIndex(1);
        }
        else {
            m_portnames.setCurrentIndex(0);
            m_portnames.setDefaultIndex(0);
        }
#endif

    };
    SerialConfig_Preset make_preset() override;
    void set_preset(const SerialConfig_Preset& _preset) override;

};


#endif // QSERIALPORTCONFIGJNI_H
